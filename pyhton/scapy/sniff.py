from scapy.all import sniff, Raw, wrpcap
import threading
import time
import signal

e = threading.Event()


def handler(signum, frame):
    global e
    e.set()


def sniff_with_signal():
    global e
    pcap = sniff(iface=['wlxe84e063348c8', 'lo'], stop_filter=lambda p: e.is_set())
    #pcap = sniff(iface=['wlxe84e063348c8', 'lo'],
    #             stop_filter=lambda p: p.haslayer(Raw) and 'stopflag' in p.getlayer(Raw).load)
    wrpcap('/tmp/test.pcap', pcap)
    print('pcap has wrote into file /tmp/test.pcap')


def main():
    signal.signal(signal.SIGTERM, handler)
    thread = threading.Thread(target=sniff_with_signal)
    thread.start()

    while True:
        thread.join(2)
        if thread.is_alive():
            print('thread is alive')
        else:
            break


if __name__ == '__main__':
    main()
