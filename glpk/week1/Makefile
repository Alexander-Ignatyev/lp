usage:
	@echo "\tUSAGE: make ex1|ex1_model|diet|diet_set"

ex1:
	glpsol --math ex1.ampl

ex1_model:
	glpsol --model standard_form.model --data ex1.data

diet:
	glpsol --model diet.model --data diet.data

diet_set:
	glpsol --model diet_set.model --data diet_set.data
