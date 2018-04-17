<?PHP
// ------------------------------------------------------------
// 2010/10/20 Y.Matsukawa	¿·µ¬ºîÀ®
// ------------------------------------------------------------
$header[$carrier->G_AGENT_TYPE] = 1;
$body[$carrier->G_AGENT_TYPE]   = 1;
$footer[$carrier->G_AGENT_TYPE] = 1;

if ($carrier->isANDROID()) {
	$header["Android"] = 1;
	$body["Android"]   = 1;
	$footer["Android"] = 1;
}
if ($carrier->isSmartPhone()) {
	$header["SmartPhone"] = 1;
	$body["SmartPhone"]   = 1;
	$footer["SmartPhone"] = 1;
}

?>
