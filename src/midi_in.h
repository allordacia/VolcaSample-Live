#ifndef MIDI_IN_H
#define MIDI_IN_H
#ifdef __cplusplus
  extern "C"
  {
#endif

#define MIDI_NOTE_OFF 8
#define MIDI_NOTE_ON 9
#define MIDI_PROGRAM_CHANGE 12
#define MIDI_CC 11
#define MIDI_CC_PAN 10
#define MIDI_CC_EQ_BASS 20
#define MIDI_CC_EQ_TREBLE 21

struct midi_event_t {
  uint8_t code;
  uint8_t note;
  uint8_t velocity;
  uint8_t channel;
};

uint8_t *get_channel_lut(void);

#ifdef __cplusplus
}
#endif
#endif