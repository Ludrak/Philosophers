#!/bin/bash
if [[ $1 == "cleanup" ]] ; then
	make -C philo_one fclean
	make -C philo_two fclean 
	make -C philo_three fclean
elif [[ $1 == "re" ]] ; then
	make -C philo_one re
	make -C philo_two re
	make -C philo_three re
else
	make -C philo_one
        make -C philo_two
        make -C philo_three
fi
