class TuringMachine:
    def __init__(self, statetable, start, end):
        self.alphabet = statetable[0].split("|")
        self.state_count = len(statetable)
        self.alphabet_size = len(self.alphabet)
        states = dict()
        for i in range(1, self.state_count):
            state = dict()
            state_list = statetable[i].split("|")
            for j in range(self.alphabet_size):
                state[self.alphabet[j]] = state_list[j+1].split(";")
            states[state_list[0]] = state
        self.states = states
        self.endstate = end
        self.cur_state = start
        self.cur_pos = 0
        self.string = " "

    def step(self):
        if self.cur_pos == len(self.string):
            self.string.append(" ")
        action = self.states[self.cur_state][self.string[self.cur_pos]]
        self.string[self.cur_pos] = action[0]
        if action[1] == "L":
            self.cur_pos -= 1
        elif action[1] == "R":
            self.cur_pos += 1
        self.cur_state = action[2]

    def compute(self, string):
        self.string = list(string)
        log = [self.cur_state]
        while self.cur_state != self.endstate:
            self.step()
            log.append(self.cur_state)
        return ''.join(self.string), ' '.join(log)


table = ["a|b|c| |X",
         "q1|a;L;q2|b;L;q2|c;L;q2| ;R;q1|null",
         "q2|X;R;q3|X;R;q3|X;R;q3|X;R;q3|X;R;q3",
         "q3|a;R;q3|b;R;q3|c;R;q3|X;L;l2|null",
         "l1|a;L;l1|b;L;l1|c;L;l1|null|X;L;l2",
         "l2| ;R;ra1| ;R;rb1| ;R;rc1| ;L;l2| ;N;q4",
         "ra1|null|null|null| ;R;ra1|X;R;ra2",
         "rb1|null|null|null| ;R;rb1|X;R;rb2",
         "rc1|null|null|null| ;R;rc1|X;R;rc2",
         "ra2|a;R;ra2|b;R;ra2|c;R;ra2|a;L;l1|X;R;ra2",
         "rb2|a;R;rb2|b;R;rb2|c;R;rb2|b;L;l1|X;R;rb2",
         "rc2|a;R;rc2|b;R;rc2|c;R;rc2|c;L;l1|X;R;rc2",
         "q4|null|null|null| ;R;q4| ;N;end"
         ]
tm = TuringMachine(table, "q1", "end")
print(tm.compute(input())[0])