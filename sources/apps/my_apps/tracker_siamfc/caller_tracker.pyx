import sys
sys.path.insert(0, '')

from TrackerSiamFC import trackersiamfc

cdef public void call_tracker():
    trackersiamfc()
