<?php
require_once('/home/emap/src/smt/inc/define.inc');
?>

var gip_api = '<?php echo($API_JSAPI_SRV_API_FOR_PATCH); ?>';
var gip_map = '<?php echo($API_JSAPI_SRV_MAP_FOR_PATCH); ?>';

if (ZDC_SSL == 1) {
    ZdcHttpRequest.setProxyDomain(gip_api);
    ZdcMapServer  = 'https://' + gip_api + '/mapapi/';
    ZdcMapLog     = 'https://' + gip_api + '/mapapi/img/back-logo.gif';
}else{
    ZdcHttpRequest.setProxyDomain(gip_api);  
    ZdcMapServer  = 'http://' + gip_api + '/mapapi/';
    ZdcMapLog     = 'http://' + gip_api + '/mapapi/img/back-logo.gif';
}
ZdcTileServers = gip_map;

ZdcCommon.ZdcMapServer  = ZdcMapServer;
ZdcCommon.ZdcTileServer = ZdcTileServer;
ZdcCommon.ZdcMapLog     = ZdcMapLog;
ZdcCommon.ZdcMapAccess  = ZdcMapAccess;

ZdcHttpRequest.setProxyDomain(gip_api);