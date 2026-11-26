import pathlib
import random
import subprocess
import sys


executable = str(pathlib.Path(sys.argv[1]).resolve())


def check(data, expected):
    result = subprocess.run(
        [executable], input=data, text=True, capture_output=True, check=True
    )
    assert result.stdout.split() == expected.split(), (data, result.stdout, expected)
    assert len(result.stdout.splitlines()) == len(expected.splitlines())


for seed in range(200):
    rng = random.Random(seed)
    initial = [rng.randint(-100, 100) for _ in range(rng.randint(1, 40))]
    values = initial[:]
    commands = []
    answers = []
    for _ in range(1000):
        op = rng.choice([1, 3, 4, 6] + ([2, 5] if values else []))
        if op == 1:
            index = rng.randrange(len(values) + 1)
            value = rng.choice([-2147483648, 2147483647, rng.randint(-100, 100)])
            commands.append(f"1 {index} {value}")
            values.insert(index, value)
        elif op == 2:
            index = rng.randrange(len(values))
            commands.append(f"2 {index + 1}")
            values.pop(index)
        elif op == 3:
            commands.append("3")
            for index in range(0, len(values) - 1, 2):
                values[index], values[index + 1] = values[index + 1], values[index]
        elif op == 4:
            count = rng.randrange(len(values) + 1)
            distance = rng.randrange(len(values) - count + 1)
            commands.append(f"4 {count} {distance}")
            values = values[count:count + distance] + values[:count] + values[count + distance:]
        elif op == 5:
            index = rng.randrange(len(values))
            commands.append(f"5 {index + 1}")
            answers.append(str(values[index]))
        else:
            commands.append("6")
            answers.append(" ".join(map(str, values)))
    data = f"{len(initial)}\n" + " ".join(map(str, initial)) + "\n"
    data += f"{len(commands)}\n" + "\n".join(commands) + "\n"
    check(data, "\n".join(answers) + "\n")

print("Passed 200 randomized cases (200,000 operations).")
