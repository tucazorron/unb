END_WORD = 'Hasta la vista, beibe!'
TABLE_DIVISIONS = '+---------------+----------+----------+----------+----------+----------+----------+'
WEEK_DAYS_HEADER = '|               | Seg      | Ter      | Qua      | Qui      | Sex      | Sab      |'
SPACE_CELL = ' ' * 8
CLASS_SCHEDULES = [
    '| 08:00 - 08:55 |',
    '| 08:55 - 09:50 |',
    '| 10:00 - 10:55 |',
    '| 10:55 - 11:50 |',
    '| 12:00 - 12:55 |',
    '| 12:55 - 13:50 |',
    '| 14:00 - 14:55 |',
    '| 14:55 - 15:50 |',
    '| 16:00 - 16:55 |',
    '| 16:55 - 17:50 |',
    '| 18:00 - 18:55 |',
    '| 19:00 - 19:50 |',
    '| 19:50 - 20:40 |',
    '| 20:50 - 21:40 |',
    '| 21:40 - 22:30 |',
]

timeTable = [[SPACE_CELL for i in range(6)] for j in range(15)]


def printWeekDaysHeader():
    print(TABLE_DIVISIONS)
    print(WEEK_DAYS_HEADER)
    print(TABLE_DIVISIONS)


def printTableRank(timeRange, rank):
    print(CLASS_SCHEDULES[timeRange], end='')
    for cell in rank:
        print(f' {cell} |', end='')
    print()
    print(TABLE_DIVISIONS)


def printTimeTable():
    printWeekDaysHeader()
    for i in range(15):
        for j in range(6):
            if timeTable[i][j] != SPACE_CELL:
                printTableRank(i, timeTable[i])
                break


def handleWeekDays(weekDays):
    return [int(x) - 2 for x in weekDays]


def handleDayTurn(dayTurn):
    if dayTurn == 'M':
        return -1
    elif dayTurn == 'T':
        return 4
    elif dayTurn == 'N':
        return 10


def handleSchedules(schedules):
    return [int(x) for x in schedules]


def decodeSchedules(weekDays, dayTurn, schedules):
    finalSchedules = []
    for weekDay in weekDays:
        for schedule in schedules:
            finalSchedules.append([schedule + dayTurn, weekDay])
    return finalSchedules


def handleEncodedSchedules(encodedSchedules):
    aux = []
    for schedule in encodedSchedules:
        for index in range(len(schedule)):
            if schedule[index].isalpha():
                weekDays = handleWeekDays(schedule[:index])
                dayTurn = handleDayTurn(schedule[index])
                schedules = handleSchedules(schedule[index + 1:])
                break
        aux.extend(decodeSchedules(weekDays, dayTurn, schedules))
    return aux


def handleInput(userInput):
    comand = [x for x in userInput.split()]
    action = comand[0]
    code = comand[1]
    schedules = handleEncodedSchedules(comand[2:])
    return action, code, schedules


def addSubjects(code, schedules):
    for i, j in schedules:
        if timeTable[i][j] != SPACE_CELL:
            return 'ERROR'
    for i, j in schedules:
        timeTable[i][j] = code


def removeSubjects(code, schedules):
    for i, j in schedules:
        if timeTable[i][j] != code:
            return 'ERROR'
    for i, j in schedules:
        timeTable[i][j] = SPACE_CELL


def printErrorMessage(userInput):
    print(f'!({userInput})')


def program():
    while True:
        userInput = input()
        if userInput == END_WORD:
            break
        elif userInput == '?':
            printTimeTable()
        else:
            action, code, schedules = handleInput(userInput)
            if action == '+':
                response = addSubjects(code, schedules)
            else:
                response = removeSubjects(code, schedules)
            if response == 'ERROR':
                printErrorMessage(userInput)


program()
