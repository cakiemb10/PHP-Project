# Ver10.00	2008/12/14	T.Ogawa		e-map IKOU ISHOKU -> froffice

# Ver10.00 mod [
#	# Oracle8Server Enviroment
#	setenv ORACLE_BASE /usr/local/oracle
#	setenv ORACLE_HOME $ORACLE_BASE/product/8.1.7
#	setenv ORACLE_SID EMAP
# Oracle9i R9.2.0 Enviroment
setenv ORACLE_BASE /opt/app/oracle
setenv ORACLE_HOME $ORACLE_BASE/product/10.2.0/client
setenv ORACLE_SID EMAP
# Ver10.00 mod ]
setenv ORACLE_TERM vt100
setenv ORACLE_OWNER oracle
setenv ORA_NLS33 $ORACLE_HOME/nls/admin/data
setenv NLS_LANG Japanese_Japan.JA16EUC
setenv TMPDIR /var/tmp

# PathSetting
set path=( . )
set path=( $path $ORACLE_HOME/bin  )
set path=( $path /usr/local/bin    )
set path=( $path /bin              )
set path=( $path /usr/bin          )
set path=( $path /usr/X11R6/bin    )
set path=( $path /usr/local/lines/Zmap/bin )
set path=( $path /sbin             )
set path=( $path /usr/sbin         )


setenv LD_LIBRARY_PATH $ORACLE_HOME/lib
setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH\:/usr/lib
setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH\:/usr/local/lib

setenv LIBPATH $ORACLE_HOME/lib

