cmd  = "ping -c 1 192.168.137."

with open('ping.sh','w') as f:
    for i in range(255):
        f.write(cmd + format("%d" % i) + "\n")

print("done")
