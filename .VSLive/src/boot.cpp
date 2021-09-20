#include <Update.h>
#include "esp_ota_ops.h"
#include "esp_image_format.h"
#include "driver/sdmmc_host.h"
#include "esp_system.h"
#include "file_system.h"
#include "wvr_pins.h"

extern "C" esp_err_t emmc_read(void *dst, size_t start_sector, size_t sector_count);
extern "C" struct metadata_t *get_metadata(void);
extern "C" void write_metadata(struct metadata_t m);

void bootFromEmmc(int index)
{
    firmware_t *firmware = get_firmware_slot(index);
    log_i("booting firmware index %d, length %d, start_block %d", index, firmware->length, firmware->start_block);
    bool ret = Update.begin(firmware->length);
    if(!ret){
        log_e("not enough space in flash to boot this firmware");
        return;
    }
    size_t num_sectors = firmware->length / SECTOR_SIZE;
    size_t remaining = firmware->length % SECTOR_SIZE;
    size_t sector = firmware->start_block;
    uint8_t *buf = (uint8_t *)ps_malloc(SECTOR_SIZE);

    log_i("starting update");
    for(int i=0;i<num_sectors;i++){
        feedLoopWDT();
        ESP_ERROR_CHECK(emmc_read(buf,sector++,1));
        size_t written = Update.write(buf, SECTOR_SIZE);
        if(written != SECTOR_SIZE){
            log_e("didn't finish writting sector");
            Update.abort();
            break;
        } else {
            printf(".");
        }
    }
    ESP_ERROR_CHECK(emmc_read(buf,sector++,1));
    size_t written = Update.write(buf, remaining);
    if(written != remaining){
        log_e("didn't finish writting sector");
        Update.abort();
    } else {
        log_e("done writting");
    }
    feedLoopWDT();
    if(Update.end()){
        if(Update.isFinished()){
            log_e("success");
            free(buf);
            metadata_t *new_metadata = get_metadata();
            new_metadata->current_firmware_index = index;
            new_metadata->current_website_index = index;
            write_metadata(*new_metadata);
            sdmmc_host_deinit();
            feedLoopWDT();
            // delay(1000);
            ESP.restart();
        } else {
            log_e("Update.isFinished() : false");
        }
    } else {
        log_e("Update.end() : false");
    }
    free(buf);
}

void boot_into_recovery_mode(void)
{
    int index = -1;
    firmware_t *firmware = get_firmware_slot(index);
    log_i("booting firmware index %d, length %d, start_block %d", index, firmware->length, firmware->start_block);
    bool ret = Update.begin(firmware->length);
    if(!ret){
        log_e("not enough space in flash to boot this firmware");
        return;
    }
    size_t num_sectors = firmware->length / SECTOR_SIZE;
    size_t remaining = firmware->length % SECTOR_SIZE;
    size_t sector = firmware->start_block;
    uint8_t *buf = (uint8_t *)ps_malloc(SECTOR_SIZE);

    log_i("starting update");
    for(int i=0;i<num_sectors;i++){
        ESP_ERROR_CHECK(emmc_read(buf,sector++,1));
        size_t written = Update.write(buf, SECTOR_SIZE);
        if(written != SECTOR_SIZE){
            log_e("didn't finish writting sector");
            Update.abort();
            break;
        } else {
            printf(".");
        }
    }
    ESP_ERROR_CHECK(emmc_read(buf,sector++,1));
    size_t written = Update.write(buf, remaining);
    if(written != remaining){
        log_e("didn't finish writting sector");
        Update.abort();
    } else {
        log_e("done writting");
    }
    if(Update.end()){
        if(Update.isFinished()){
            log_e("success");
            free(buf);
            metadata_t *new_metadata = get_metadata();
            new_metadata->current_firmware_index = index;
            write_metadata(*new_metadata);
            // sdmmc_host_deinit();
            feedLoopWDT();
            // delay(1000);
            ESP.restart();
        } else {
            log_e("Update.isFinished() : false");
        }
    } else {
        log_e("Update.end() : false");
    }
    free(buf);
}

int check_for_recovery_mode(void)
{
    metadata_t *new_metadata = get_metadata();
    if(!new_metadata->should_check_strapping_pin)
    {
        // do a normal boot
        return 1;
    }
    gpio_reset_pin(gpio_pins[new_metadata->recovery_mode_straping_pin]);
    pinMode(wvr_pins[new_metadata->recovery_mode_straping_pin], INPUT_PULLUP);
    int res = digitalRead(wvr_pins[new_metadata->recovery_mode_straping_pin]);
    log_i("strapping pin %d reads %d",new_metadata->recovery_mode_straping_pin,res);
    return res;
}