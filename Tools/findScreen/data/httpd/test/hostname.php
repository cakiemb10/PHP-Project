<?php

	if($_GET["host_name"]) {
		$host_name = $_GET["host_name"];
	}


	if ($host_name) {
		$result = dns_get_record($host_name, DNS_ALL);
		echo "<PRE>";print_r($result);echo "</PRE>";
	}
?>
