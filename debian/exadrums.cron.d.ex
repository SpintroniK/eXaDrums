#
# Regular cron jobs for the exadrums package
#
0 4	* * *	root	[ -x /usr/bin/exadrums_maintenance ] && /usr/bin/exadrums_maintenance
