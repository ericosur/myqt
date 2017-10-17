# demo to use two kinds of players with same interface

class BasicPlayer defines common interfaces
class MusicPlayer and VideoPlayer are children of class BasicPlayer, with
common interface:
* playFile() -- pure virtual
* pause() -- pure virtual
* getName()
