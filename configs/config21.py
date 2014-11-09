_base_path='data/week2/part1TestCases/'

tests = []
test_results = []
tests += [_base_path+'unitTests/dict{}'.format(i) for i in xrange(1, 11)]
test_results += [_base_path+'unitTests/dict{}.output'.format(i) for i in xrange(1, 11)]

task_result_path = 'results/homework21'
tasks = [_base_path+'assignmentParts/part{}.dict'.format(i) for i in xrange(1, 6)]
task_results = [task_result_path+'/part{}.dict.output'.format(i) for i in xrange(1, 6)]

binary_path = 'build/homework21'
