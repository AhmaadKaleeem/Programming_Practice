from PyQt5 import QtWidgets
from ui_mainwindow import Ui_MainWindow
from sound_recorder_gui import SoundRecorder
from PyQt5.QtWidgets import QFileDialog, QMessageBox
import sys

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        
        self.ui.setupUi(self)
        self.ui.tabWidget.tabBar().setVisible(False)
        self.recorder = SoundRecorder()

        self.current_file = None

        self.ui.main_recording.clicked.connect(lambda: self.ui.stackedWidget.setCurrentWidget(self.ui.recording))
        self.ui.main_playback.clicked.connect(lambda: self.ui.stackedWidget.setCurrentWidget(self.ui.playback))
        self.ui.main_tools.clicked.connect(lambda: self.ui.stackedWidget.setCurrentWidget(self.ui.tools))

        self.ui.Dynamic_2.clicked.connect(lambda: self.ui.tabWidget.setCurrentWidget(self.ui.Dynamic))
        self.ui.Static_2.clicked.connect(lambda: self.ui.tabWidget.setCurrentWidget(self.ui.Static))

        self.ui.start_dynamic.clicked.connect(self.start_dynamic_recording)
        self.ui.stop_dynamic.clicked.connect(self.stop_dynamic_recording)

        self.ui.start_static.clicked.connect(self.start_static_recording)

        self.ui.file_button.clicked.connect(self.select_file)
        self.ui.start_playback.clicked.connect(self.start_playback)
        self.ui.pause_playback.clicked.connect(self.pause_playback)
        self.ui.stop_playback.clicked.connect(self.stop_playback)

        self.ui.normalize.clicked.connect(self.normalize_file)
        self.ui.trim.clicked.connect(self.trim_file)
        self.ui.delete_2.clicked.connect(self.delete_file)
        self.ui.file_selection.clicked.connect(self.select_file_tools)

    def start_dynamic_recording(self):
        self.recorder.set_channels(1) 
        self.recorder.start_dynamic()
        QMessageBox.information(self, "Recording", "Dynamic recording started.\nPress 'Stop Recording' to finish.")

    def stop_dynamic_recording(self):
        data = self.recorder.stop_dynamic()
        if data is not None:
            fname, _ = QFileDialog.getSaveFileName(self, "Save Recording", "dynamic.wav", "WAV files (*.wav)")
            if fname:
                self.recorder.save(data, fname)
                self.current_file = fname
                self.ui.file_name.setText(f"Selected File: {fname}")
                QMessageBox.information(self, "Saved", f"Recording saved as {fname}")

    def start_static_recording(self):
        self.recorder.set_channels(1)
        duration, ok = QtWidgets.QInputDialog.getInt(self, "Duration", "Record for how many seconds?", 5, 1, 300)
        if ok:
            data = self.recorder.record_fixed_time(duration)
            fname, _ = QFileDialog.getSaveFileName(self, "Save Recording", "fixed.wav", "WAV files (*.wav)")
            if fname:
                self.recorder.save(data, fname)
                self.current_file = fname
                self.ui.file_name.setText(f"Selected File: {fname}")
                QMessageBox.information(self, "Saved", f"Recording saved as {fname}")

    def select_file(self):
        fname, _ = QFileDialog.getOpenFileName(self, "Select WAV File", "", "WAV files (*.wav)")
        if fname:
            self.current_file = fname
            self.ui.file_name.setText(f"Selected File: {fname}")

    def start_playback(self):
        if not self.current_file:
            self.select_file()
        if self.current_file:
            self.recorder.playback(self.current_file)

    def pause_playback(self):
        sd = self.recorder  # shortcut
        try:
            sd.stop_playback()
        except Exception:
            pass

    def stop_playback(self):
        sd = self.recorder  
        try:
            sd.stop_playback()
        except Exception:
            pass

    def normalize_file(self):
        if not self.current_file:
            QMessageBox.warning(self, "No file", "Select a file first.")
            return
        outname = self.recorder.normalize_file(self.current_file)
        QMessageBox.information(self, "Normalized", f"Normalized file saved as {outname}")

    def trim_file(self):
        if not self.current_file:
            QMessageBox.warning(self, "No file", "Select a file first.")
            return
        outname = self.recorder.trim_silence_file(self.current_file)
        QMessageBox.information(self, "Trimmed", f"Trimmed file saved as {outname}")

    def delete_file(self):
        if not self.current_file:
            QMessageBox.warning(self, "No file", "Select a file first.")
            return
        self.recorder.delete_file(self.current_file)
        QMessageBox.information(self, "Deleted", f"Deleted {self.current_file}")
        self.current_file = None
        self.ui.file_name.setText("Selected File:")

    def select_file_tools(self):
        self.select_file()

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())