import numpy as np
# Normalize the sound
def normailze(audio: np.ndarray):
    max_vol = np.max(np.abs(audio))
    if max_vol <= 0:
        return audio.astype("float32")
    return (audio/max_vol).astype("float32")

def trim_silence(audio: np.ndarray , threshold = 0.01):
    if audio.ndim > 1:
        mono = np.mean(np.abs(audio), axis=1)
    else:
        mono = np.abs(audio)
    indexes = np.where(mono > threshold)[0]
    if indexes == 0:
        return audio[0:0]
    start,end = indexes[0],indexes[-1] + 1
    return audio[start:end]