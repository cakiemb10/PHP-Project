<?php
/*
 *  add 2014/12/24 ChienNguyen
 *  Function: write log to file
 *  Return: boolean
*/
function output_gpslog($message = '',$file_name='') {
    $dir_log = '/home/emap/logs/';
    $path_log = $dir_log.$file_name;

    if (!$fp = @fopen($path_log, 'a')) {
        return FALSE;
    }

    fwrite($fp, $message);

    fclose($fp);

    return TRUE;

}


/**
* 
*/
class GpsLogFunc{
    
    /*
     * getMeshAddress
     *
     *  param: mesh dime (1st - 5th)
     *         lat(mili sec)
     *         lon(mili sec)
     *
     * return meshAdd
     */
    function getMeshAddress($dime, $lat, $lon) {

        $m1Lat = floor($lat / 3600 / 1000 * 1.5);
        $m1Lon = floor($lon / 3600 / 1000 - 100);

        $calLat1 = $this->fmod2($lat, 2400 * 1000);
        $calLon1 = $this->fmod2($lon, 3600 * 1000);

        $calLat2 = $this->fmod2($calLat1, 300 * 1000);
        $calLon2 = $this->fmod2($calLon1, 450 * 1000);

        $calLat3 = $this->fmod2($calLat2, 30 * 1000);
        $calLon3 = $this->fmod2($calLon2, 45 * 1000);

        $calLat4 = $this->fmod2($calLat3, 15   * 1000);
        $calLon4 = $this->fmod2($calLon3, 22.5 * 1000);

        $calLat5 = $this->fmod2($calLat4, 7.5   * 1000);
        $calLon5 = $this->fmod2($calLon4, 11.25 * 1000);

        $m2Lat = floor($calLat1 / 300 / 1000);
        $m2Lon = floor($calLon1 / 450 / 1000);

        $m3Lat = floor($calLat2 / 30 / 1000);
        $m3Lon = floor($calLon2 / 45 / 1000);

        $m4Lat = floor($calLat3 / 15 / 1000);
        $m4Lon = floor($calLon3 / 22.5 / 1000);

        $m5Lat = floor($calLat4 / 7.5 / 1000);
        $m5Lon = floor($calLon4 / 11.25 / 1000);

        $m4 = (2 * $m4Lat) + ($m4Lon + 1);
        $m5 = (2 * $m5Lat) + ($m5Lon + 1);

            //mesh
        if($dime == 1) {
            $mesh = $m1Lat . $m1Lon;
        }
        else if($dime == 2) {
            $mesh = $m1Lat . $m1Lon . $m2Lat . $m2Lon;
        }
        else if($dime == 3) {
            $mesh = $m1Lat . $m1Lon . $m2Lat . $m2Lon . $m3Lat . $m3Lon;
        }
        else if($dime == 4) {
            $mesh = $m1Lat . $m1Lon . $m2Lat . $m2Lon . $m3Lat . $m3Lon . $m4;
        }
        else if($dime == 5) {
            $mesh = $m1Lat . $m1Lon . $m2Lat . $m2Lon . $m3Lat . $m3Lon . $m4 . $m5;
        }
        else {
            $mesh = "error";
        }
        return $mesh;

    }

    /*
     * getMeshAddress
     *
     *  param: meshcode
     *
     * return lat lon(left low / right high)
     */
    function getMeshToLatLon($meshcode) {

        if (!preg_match('/^\d{10}$/', $meshcode)) {
            return -1;
        }

        $m = sscanf($meshcode, "%2d%2d%1d%1d%1d%1d%1d%1d");

        $m4Mesh = intval($m[6]) - 1;
        $m4Lat = floor($m4Mesh / 2);
        $m4Lon = $m4Mesh % 2;
        $m5Mesh = intval($m[7]) - 1;
        $m5Lat = floor($m5Mesh / 2);
        $m5Lon = $m5Mesh % 2;

        $left_low_lat = (($m[0] / 1.5) * 3600 + ($m[2] * 5) * 60 + $m[4] * 30 + $m4Lat * 15 + $m5Lat * 7.5) * 1000;
        $left_low_lon = (($m[1] + 100) * 3600 + ($m[3] * 7.5) * 60 + $m[5] * 45 + $m4Lon * 22.5 + $m5Lon * 11.25) * 1000;

        //250m plus
        $right_high_lat = $left_low_lat + (30 * 250);
        $right_high_lon = $left_low_lon + (45 * 250);

        //125m plus
        $center_lat = $left_low_lat + (30 * 125);
        $center_lon = $left_low_lon + (45 * 125);

        return array(  "meshcode"       => $meshcode
            , "left_low_lat"   => $left_low_lat
            , "left_low_lon"   => $left_low_lon
            , "right_high_lat" => $right_high_lat
            , "right_high_lon" => $right_high_lon
            , "center_lat"     => $center_lat
            , "center_lon"     => $center_lon
            ); 
    }

    function fmod2($n, $b) {
        $i = (int) floor($n / $b);
        $res = $n - $b * $i;

        return (int) $res;
    }


}