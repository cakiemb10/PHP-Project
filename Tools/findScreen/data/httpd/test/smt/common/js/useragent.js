function getUA(){
  var ua = navigator.userAgent;
  var agent = "";

  if (ua.indexOf('iPhone') > 0 || ua.indexOf('iPod') > 0 || ua.indexOf('Android') > 0) {
        agent = "unrecognized";
  }else{
    if (ua.match(/MSIE (\d\.\d+)/)) {
        if (ua.match(/Trident\/4\.0/)) {
            agent = "IE8";
        }else if(ua.match(/msie 6/i)){
            agent = "IE7";
        }else if ( ua.match( /msie[^0-9a-zA-Z]*([0-9.]+[^;])/i ) ) {
            agent = "IE 4.x以前";
        }else {
            agent = "IE" + RegExp.$1;
        }
    }


    else if(ua.match(/firefox/i))
        agent = "firefox";
    else if(ua.match(/opera/i))
        agent = "opera";
    else if(ua.match(/netscape/i))
        agent = "netscape";
    else if(ua.match(/safari/i)){
        if(ua.match(/chrome/i))
            agent = "chrome";
        else
            agent = "safari";
    }
    else{
        agent = "unrecognized";
    }
  }

    return agent;
}



