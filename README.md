# CyberChaCha

CyberChaCha contains code for running a robot that listens to audio and responds by dancing.

## Setup
- This is the data the model was trained on (each audio truncated to 10 seconds). No need to download this.\
Dataset: [GTZAN Audio Dataset](https://www.kaggle.com/datasets/andradaolteanu/gtzan-dataset-music-genre-classification?select=Data)
- Download the .dat files here: [Data Files](https://www.dropbox.com/sh/ggbf91bei6ibt6z/AACWjYXoWEJ3r9lukxt9IaY_a?dl=0) and place them in /dat_files
- Dependencies:
    - ESP32Servo
    - Adafruit_SSD1306
    - NumPy
    - SciPy
    - Aubio
    - Librosa
    - scikit-learn

## Usage
Upload "RecordingAudioFromMX4466\RecordingAudioFromMX4466.ino" to your arduino. Connect MX4466 microphone to pin 14 (or change the pin number in RecordingAudioFromMX4466\RecordingAudioFromMX4466.ino)\
```python
#define MIC_PORT <your port number>
```
Upload "arduino_robot\arduino_robot.ino" to your arduino on a different port. Connect robot servos and lcd display to pins according to the pin numbers in setup(), or change accordingly.\
```python
Serial.begin(BAUD_RATE);
  leftShoulder.attach(<port number>);
  rightShoulder.attach(<port number>);
  rightElbow.attach(<port number>);
  leftElbow.attach(<port number>);
  leftLeg.attach(<port number>);
  rightLeg.attach(<port number>);
  leftKnee.attach(<port number>);
  rightKnee.attach(<port number>);
  body.attach(<port number>);
  head.attach(<port number>);
```
In "audio.py" make sure to change your ports to the correct ones (PORT and PORT2 variables)\
```python
PORT = '<your port>' # microphone
PORT2 = '<your other port>' # motors
```
In the terminal:
```bash
python audio.py
```
Note: There may be an error on reading bytes. Just run it again. The robot will move after 10 seconds, with audio recordings being placed in /output folder
