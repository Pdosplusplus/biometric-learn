#!/bin/sh

################################################################################
# Establecer las variables de entorno. Éstas implican haber instalado primero  #
# libtool, automake y autoconf, y compilado desde fuentes: libwww de w3c y     #
# xmlrpc.1.25.26 (en ese orden), habiendo corregido los enlaces simbólicos     #
# faltantes.                                                                   #
################################################################################
CLIENT_CFLAGS=`xmlrpc-c-config c++ libwww-client --cflags`
CLIENT_LIBS=`xmlrpc-c-config c++ libwww-client --libs`
CGI_CFLAGS=`xmlrpc-c-config cgi-server --cflags`
CGI_LIBS=`xmlrpc-c-config cgi-server --libs`

g++ $CGI_CFLAGS $CLIENT_CFLAGS \
  server.cpp -o \
  server.cgi \
  $CGI_LIBS $CLIENT_LIBS

##############################
# Copiar el binario (.cgi)   #
##############################
mkdir -p /usr/lib/cgi-bin/server_pruebas/
cp server.cgi /usr/lib/cgi-bin/server_pruebas/

##################################################################
# Otorgar permisos y establecer el propietario de los archivos:  #
##################################################################
chmod 740 /usr/lib/cgi-bin/ -R
chown www-data:www-data /usr/lib/cgi-bin/ -R
