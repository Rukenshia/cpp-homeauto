# cpp-homeauto
this is a project I made back in 2014 with the first-gen raspberry pi. it is a simple home automation providing a UDP API. a HTTP API can be found in [Rukenshia/homeauto-api](https://github.com/Rukenshia/homeauto-api). I also made a [Go version](https://github.com/Rukenshia/go-homeauto) of the home automation.

I did fix a few bugs when pushing this repository to GitHub like a memory leak in `Server::Process`. The current server handles around 52k requests per second (benchmarked using `timeout 1s udpsend/udpsend`):

```
Command being timed: "bin/RPi_Automation"
    User time (seconds): 0.37
    System time (seconds): 0.29
    Percent of CPU this job got: 2%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:28.14
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 3616
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 0
    Minor (reclaiming a frame) page faults: 142
    Voluntary context switches: 52779
    Involuntary context switches: 47
    Swaps: 0
    File system inputs: 0
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0
```

### Building
you need to have boost-1.6 installed as well as yaml-cpp compiled manually. then you should be able to just run `make`.
