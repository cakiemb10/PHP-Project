<html><title>華屋与兵衛 - 店舗検索</title>
<!--{def iPhone}--><meta name="viewport" content="width=280;"><!--{/def}-->
<!--{def Android}--><meta name="viewport" content="width=280;"><!--{/def}-->
<!--{def Android_1}--><script type="text/javascript" src="gears_init.js"></script><!--{/def}-->
<!--{def iPhone}-->
<script type="text/javascript">
function locupdate(pos){
var lat = pos.coords.latitude;var lon = pos.coords.longitude;
window.location.href = "{rval ima_url}"+"&lat="+lat+"&lon="+lon+"&geo=wgs84";
}
function handleError(err) {
alert("現在地の取得に失敗しました");
}
</script>
<!--{/def}-->
<!--{def Android_1}-->
<script type="text/javascript">
var geo = google.gears.factory.create('beta.geolocation');
function updatePosition(pos) {
var lat = pos.latitude; var lon = pos.longitude;
window.location.href = "{rval ima_url}"+"&lat="+lat+"&lon="+lon+"&geo=wgs84";
}
function handleError(err) {alert("現在地の取得に失敗しました");}
</script>
<!--{/def}-->
<!--{def Android_2}-->
<script type="text/javascript">
function locupdate(pos){
var lat = pos.coords.latitude;var lon = pos.coords.longitude;
window.location.href = "{rval ima_url}"+"&lat="+lat+"&lon="+lon+"&geo=wgs84";
}
function handleError(err) {
alert("現在地の取得に失敗しました");
}
</script>
<!--{/def}-->
<body>
<center>
<img border="0" alt="\"Loading...\"" src="{rval D_DIR_COMPANY}img/logo.gif">
</center>
