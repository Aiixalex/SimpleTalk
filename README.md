# SimpleTalk
A simple "chat"-like facility that enables someone at one terminal (or Xterm) to communicate with someone at another terminal. 

### About SimpleTalk

All four threads will share access to a list ADT:

- The keyboard input thread, on receipt of input, adds the input to the list of messages that need to be sent to the remote s-talk client.

- The UDP output thread will take each message off this list and send it over the network to the remote client.

- The UDP input thread, on receipt of input from the remote s-talk client, will put the message onto the list of messages that need to be printed to the local screen.

- The screen output thread will take each message off this list and output it to the screen.

### Getting Started

#### Installation

```
git clone https://github.com/Aiixalex/SimpleTalk/
```

```
make
```

#### Usage

The general format is:

```
s-talk [my port number] [remote machine name] [remote port number]
```

For example, user A is on machine csil-cpu4 and will use port 6001, while user B is on machine csil-cpu5 and will use port 6000.

To initilize SimpleTalk, user A should type in terminal:

```
./s-talk 6001 csil-cpu5 6000
```

And user B should type:

```
./s-talk 6000 csil-cpu4 6001
```

The result will be that every line typed at each terminal will appear on BOTH terminals: it will appear character-by-character on the sender’s terminal as they type it, and it will appear on the receiver’s terminal once the sender presses enter.
