<?php
echo("SERVER<br />\n");
print_R($_SERVER);
ini_set('memory_limit','32M');

echo("php_Info<br />\n");
phpinfo();
?>