log4php.rootLogger=debug, EMAP_SMT
log4php.appender.EMAP_SMT=LoggerAppenderDailyFile
log4php.appender.EMAP_SMT.DatePattern=YmdH
log4php.appender.EMAP_SMT.file=/home/emap/logs/log_smt_%s.log
log4php.appender.EMAP_SMT.layout=LoggerPatternLayout
log4php.appender.EMAP_SMT.layout.ConversionPattern=%d %t %p %c %L %x %m%n

