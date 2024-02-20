CSV_COMMAND = 'leia'
TEACHERS_COMMAND = 'carga'
DISCIPLINES_COMMAND = 'disciplina'
REGISTRATIONS_COMMAND = 'matriculas'
ERROR_MESSAGE = 'No hay'
EXIT_COMMAND = 'FIM'

teachers = {}
disciplines = {}
registrations = {}
codesToNames = {}


def printErrorMessage(argument):
    print(f'{ERROR_MESSAGE} {argument}...')


def showTeachers(argument):
    return 'ERROR'


def showDisciplines(argument):
    return 'ERROR'


def showRegistrations(argument):
    return 'ERROR'


def updateCodesToNames(code, name):
    codesToNames[code] = name


def updateRegistrations(code, vacanciesOccupied):
    registrations[code] = vacanciesOccupied


def updateDisciplines(code, classId, teacher):
    if code not in disciplines:
        disciplines[code] = {}
    if classId not in disciplines[code]:
        disciplines[code][classId] = []
    disciplines[code][classId].append(teacher)


def updateTeachers(teacher, code, name, classId, hours, vacanciesOccupied):
    if teacher not in teachers:
        teachers[teacher] = {}
    teachers[teacher][code] = {
        'name': name,
        'classId': classId,
        'hours': hours,
        'vacanciesOccupied': vacanciesOccupied
    }


def handleTeacherAndHours(teacherAndHours):
    teacher, hours = teacherAndHours.split()
    hours = int(hours[1:3])
    return teacher, hours


def readCSV(argument):
    file = open(argument, 'r')
    rows = file.readlines()
    for row in rows:
        code, name, classId, period, teacherAndHours, schedule, vacanciesOffered, vacanciesOccupied, local = row.split(',')
        teacher, hours = handleTeacherAndHours(teacherAndHours)
        updateTeachers(teacher, code, name, classId, hours, vacanciesOccupied)
        updateDisciplines(code, classId, teacher)
        updateRegistrations(code, vacanciesOccupied)
        updateCodesToNames(code, name)
    file.close()
    return 'OK'


def handleInput(command):
    return command.split(' ', 1)


def program():
    while True:
        command = input()
        if command == EXIT_COMMAND:
            break
        action, argument = handleInput(command)
        if action == CSV_COMMAND:
            actionResult = readCSV(argument)
        elif action == TEACHERS_COMMAND:
            actionResult = showTeachers(argument)
        elif action == DISCIPLINES_COMMAND:
            actionResult = showDisciplines(argument)
        elif action == REGISTRATIONS_COMMAND:
            actionResult = showRegistrations(argument)
        if actionResult == 'ERROR':
            printErrorMessage(argument)


program()
