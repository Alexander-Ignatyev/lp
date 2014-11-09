import sys
import os
import os.path
import shutil
import subprocess

sys.path.append('configs')

# import homework settings
# import config21 as config  # Homework 2.1
# import config22 as config  # Homework 2.2
import config31 as config  # Homework 3.1

def run_solver(args):
    process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    return_code = process.returncode
    return return_code, stdout, stderr

def check_results(result, pattern):
    SEP = '\n'
    EPS = 0.001
    discreps = []
    for result_line, pattern_line in zip(result.split(SEP), pattern.split(SEP)):
        result_line = result_line.strip()
        pattern_line = pattern_line.strip()
        equals = result_line == pattern_line
        if not equals:
            try:
                result_val = float(result_line)
                pattern_val = float(pattern_line)
                equals = abs(result_val - pattern_val) < EPS
            except:
                pass
        if not equals:
            discreps.append((result_line, pattern_line))
    return discreps

def run_test(test_path, result_path):
    test_name = os.path.basename(test_path)
    return_code, data, debug_data = run_solver([config.binary_path, test_path])
    if return_code != 0:
        print 'running', test_name, 'FAILED with return code =', return_code
        print 'stdout: <<', data, '>>'
        print 'stderr: <<', debug_data, '>>'
        return False
    result = True
    with open(result_path, 'r') as f:
        result_data = f.read()
    discreps = check_results(data, result_data)
    result = len(discreps) == 0
    if discreps:
        print test_name, 'FAILED'
        print debug_data
        for result_line, pattern_line in discreps:
            print '\tobtained:', result_line, 'but expected:', pattern_line
    return result

def run_task(task_path, result_path):
    task_name = os.path.basename(task_path)
    return_code, data, debug_data = run_solver([config.binary_path, task_path])
    if return_code != 0:
        print 'running', task_name, 'FAILED with return code =', return_code
        print 'stdout: <<', data, '>>'
        print 'stderr: <<', debug_data, '>>'
        return False
    with(open(result_path, 'w')) as f:
        f.write(data)
    return True

def main():
    tests_failed = 0
    tasks_failed = 0
    for test, test_result in zip(config.tests, config.test_results):
        if not run_test(test, test_result):
            tests_failed += 1
    if os.path.exists(config.task_result_path):
        shutil.rmtree(config.task_result_path)
    os.mkdir(config.task_result_path)
    if tests_failed == 0:
        for task, task_result in zip(config.tasks, config.task_results):
            if not run_task(task, task_result):
                tasks_failed += 1

    print 'Tests Failed', tests_failed, 'from', len(config.tests)
    if tests_failed != 0:
        print '\tno tasks have been run due to failed tests'
    else:
        print 'Tasks Failed', tasks_failed, 'from', len(config.tasks)

main()
