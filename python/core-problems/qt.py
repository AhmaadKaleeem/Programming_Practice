import sys
from PyQt5 import  QtWidgets
from PyQt5.QtWidgets import QApplication, QWidget,QMainWindow

def window():
    app = QApplication(sys.argv)
    win = QMainWindow()
    win.setGeometry(200,200,300 ,300)
    win.setWindowTitle("Sound Recorder")
    win.show()
    sys.exit(app.exec_())
    
window()
