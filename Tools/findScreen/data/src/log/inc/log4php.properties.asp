log4php.rootLogger=debug, EMAP_ASP
log4php.appender.EMAP_ASP=LoggerAppenderDailyFile
log4php.appender.EMAP_ASP.DatePattern=YmdH
log4php.appender.EMAP_ASP.file=/home/emap/logs/log_asp_%s.log
log4php.appender.EMAP_ASP.layout=LoggerPatternLayout
log4php.appender.EMAP_ASP.layout.ConversionPattern=%d %t %p %c %L %x %m%n

