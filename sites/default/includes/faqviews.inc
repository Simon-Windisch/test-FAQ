<?php
include_once('database.mysql.inc');


function status_info($limit){
	$query = "SELECT node.nid AS nid, node_data_field_redirect.field_redirect_value AS node_data_field_redirect_field_redirect_value, node.type AS node_type, node.vid AS node_vid, node.title AS node_title, node_revisions.body AS node_body, node.sticky AS node_sticky, node_revisions.timestamp AS node_revisions_timestamp 
						FROM node node  
						LEFT JOIN content_type_status node_data_field_redirect ON node.vid = node_data_field_redirect.vid 
						LEFT JOIN node_revisions node_revisions ON node.vid = node_revisions.vid 
						WHERE (node.type in ('status')) AND (node.promote <> 0) AND (node.status = 1 OR node.status is NULL)
						ORDER BY node_sticky DESC, node_revisions_timestamp DESC LIMIT 0,".$limit;
	
	$result = _db_query($query);
	$i = 1;
	
	global $user;
	
	while ($row = db_result_assoc($result)){
		$row['node_title'] = str_replace('//', '<br/>', $row['node_title']);

		if ($user->uid && !in_array('viewer',$user->roles)) {
			echo '				<p><a href="/node/'.$row['nid'].'/edit">'.$row['node_title'].'</a></p>'."\n";
			$i++;
		}else {

			if($row['node_data_field_redirect_field_redirect_value'] != ""){
				echo '				<p><a href="'.$row['node_data_field_redirect_field_redirect_value'].'">'.$row['node_title'].'</a></p>'."\n";
			}
			elseif($row['node_body'] != ""){
				echo '				<p><a href="/node/'.$row['nid'].'">'.$row['node_title'].'</a></p>'."\n";
			}
			else{
				echo '				<p>'.$row['node_title'].'</p>'."\n";
			}
			$i++;
		}  	

	}
}


function themenbereiche($mlid,$limit_subs){

# Abhängig von menu-id Kindelemente (und deren URL-Aliase) als Bloecke auslesen
	/* Alte query (v1)
	$query = "SELECT menu_links.link_title, menu_links.link_path, menu_links.mlid, menu_links.plid, menu_links.hidden, url_alias.dst
	          FROM menu_links
	          LEFT JOIN url_alias ON menu_links.link_path = url_alias.src
	          WHERE plid = '".$mlid."' AND hidden = '0'
	          ORDER BY weight ASC";
	*/
	$query = "SELECT menu_links.link_title, menu_links.link_path, menu_links.mlid, menu_links.plid, url_alias.dst
		        FROM menu_links
		        LEFT JOIN menu_node ON menu_links.mlid = menu_node.mlid
		        LEFT JOIN node ON menu_node.nid = node.nid
		        LEFT JOIN url_alias ON menu_links.link_path = url_alias.src
		        WHERE plid = '".$mlid."' AND (node.status = 1 OR node.status is NULL)
		        ORDER BY weight ASC";
	
	$result = _db_query($query);
	$total_items = db_num_rows($result);
	$i = 1;


# Abhängig von Kind-mid weitere Kindelemente (und deren URL-Aliase) als Blockcontents auslesen
	while ($row = db_result_assoc($result)){
		/* Alte subquery (v1)
		$subquery = "SELECT menu_links.link_title, menu_links.link_path, menu_links.mlid, menu_links.plid, menu_links.hidden, url_alias.dst
	          		 FROM menu_links
	          		 LEFT JOIN url_alias ON menu_links.link_path = url_alias.src
		             WHERE plid = '".$row['mlid']."' AND hidden = '0'
		             ORDER BY weight ASC LIMIT 0,".$limit_subs;
		*/
		$subquery = "SELECT menu_links.link_title, menu_links.link_path, menu_links.mlid, menu_links.plid, url_alias.dst
				        FROM menu_links
				        LEFT JOIN menu_node ON menu_links.mlid = menu_node.mlid
		        		LEFT JOIN node ON menu_node.nid = node.nid
		    		    LEFT JOIN url_alias ON menu_links.link_path = url_alias.src
								WHERE plid = '".$row['mlid']."' AND (node.status = 1 OR node.status is NULL)
				        ORDER BY weight ASC LIMIT 0,".$limit_subs;
		             
		$subresult = _db_query($subquery);
		$total_subitems = db_num_rows($subresult);
		$i_sub = 1;


# Werte ausgeben
		if(($i % 2) != 0){
			echo '<div class="panels">'."\n";
			$panelpos = " left";
		}else{
			$panelpos = "";
		}

		echo '	<div class="p50'.$panelpos.'">'."\n";
		echo '		<div class="box medium linked mother">'."\n";
		echo '			<h3 class="'.str_replace("- ","",$row['link_title']).'">'.str_replace("- ","",$row['link_title']).'</h3>'."\n";

		echo '			<ul>'."\n";
		while ($subrow = db_result_assoc($subresult)) {
			echo '				<li><a href="/'.$row['dst']."#antwort".$i_sub.'">'.$subrow['link_title'].'</a></li>'."\n";
			$i_sub++;
		}
		echo '			</ul>'."\n";
		echo '			<a href="/'.$row['dst'].'" class="bottom button">Weitere Fragen</a>'."\n";
		echo '		</div>'."\n";
		echo '	</div>'."\n";

		if(($i % 2) == 0){
			echo '</div>'."\n";
		}elseif($total_items == $i){
			echo '</div>'."\n";
		}
		$i++;
	}
}


function antworten($mlid){
	/* Alte query (v1)
	$query = "SELECT link_title, link_path, mlid, plid, hidden
		        FROM menu_links
		        WHERE plid = '".$mlid."'
		        ORDER BY weight ASC";
	*/
	$query = "SELECT menu_links.link_title, menu_links.link_path, menu_links.mlid, menu_links.plid, menu_links.weight, menu_node.mlid, node.nid, node.status
		        FROM menu_links
		        LEFT JOIN menu_node ON menu_links.mlid = menu_node.mlid
		        LEFT JOIN node ON menu_node.nid = node.nid
		        WHERE plid = '".$mlid."' AND (node.status = 1 OR node.status is NULL)
		        ORDER BY weight ASC";

	$result = _db_query($query);
	$i = 1;
	#$antworten = array();

	echo '<div class="box">'."\n";
	echo '<h3>Fragen</h3>'."\n";
	echo '<ol>'."\n";


	global $user;
	if ($user->uid && !in_array('viewer',$user->roles)) {
	
		while ($row = db_result_assoc($result)){
			echo '				<li class="item'.$i.'"><a href="/'.$row['link_path'].'/edit">'.$row['link_title'].'</a></li>'."\n";
			#$antworten[$i] = str_replace("node/","",$row['link_path']);
			$i++;
		}  	

	}else {

		while ($row = db_result_assoc($result)){
			echo '				<li class="item'.$i.'"><a href="#antwort'.$i.'">'.$row['link_title'].'</a></li>'."\n";
			#$antworten[$i] = str_replace("node/","",$row['link_path']);
			$i++;
		}  	

	}

	echo '</ol>'."\n";
	echo '</div>'."\n";

	
	/* Alte query (v1)
	$items = implode(", ", $antworten);
	
	$query2 = "SELECT node_revisions.nid, node_revisions.title, node_revisions.body
		        FROM node_revisions
		        LEFT JOIN menu_links ON node_revisions.title = menu_links.link_title
		        WHERE node_revisions.nid IN (".$items.") AND menu_links.has_children = '0'
		        ORDER BY menu_links.weight ASC";

		        #LEFT JOIN menu_links ON node_revisions.title = menu_links.link_title
	
	$query2 = "SELECT node_revisions.title, node_revisions.body
		        FROM node_revisions
		        LEFT JOIN menu_node ON node_revisions.nid = menu_node.nid
		        LEFT JOIN menu_links ON menu_node.mlid = menu_links.mlid 
		        WHERE node_revisions.nid IN (".$items.") AND menu_links.has_children = '0' AND node.status = '1'
		        ORDER BY menu_links.weight ASC";
	*/
		$query2 = "SELECT node_revisions.title, node_revisions.body, node.nid
		        FROM node_revisions
		        LEFT JOIN node ON node_revisions.nid = node.nid
		        LEFT JOIN menu_node ON node_revisions.nid = menu_node.nid
		        LEFT JOIN menu_links ON menu_node.mlid = menu_links.mlid 
		        WHERE menu_links.plid = '".$mlid."' AND (node.status = 1 OR node.status is NULL)
		        ORDER BY menu_links.weight ASC";

	$result2 = _db_query($query2);
	$i2 = 1;

	echo '<div class="box">'."\n";
	echo '<h3>Antworten</h3>'."\n";
	echo '<dl class="ordered">'."\n";

	while ($row = db_result_assoc($result2)){
#		echo '<dt class="item'.$i2.'" id="antwort'.$i2.'">'.$row['title'].'</dt>'."\n";
#		echo '<dd>'.$row['body']."\n".'<div class="metalinks"><a href="./" class="backlink">zur&uuml;ck</a> <a href="#header" class="toplink">zum Anfang</a></div></dd>'."\n";
#		$i2++;

		echo '<dt class="item'.$i2.'" id="antwort'.$i2.'">'.$row['title'].'</dt>'."\n";
		echo '<dd>'.$row['body']."\n";

		print drupal_get_form('fivestar_form_node_'. $row['nid'], 'node', $row['nid']);

		echo '<div class="metalinks"><a href="./" class="backlink">zur&uuml;ck</a> <a href="#header" class="toplink">zum Anfang</a></div></dd>'."\n";
		$i2++;
	}

	echo '</dl>'."\n";
	echo '</div>'."\n";
}


function selected_answers($limit, $mlid=611){
	$query = "SELECT menu_links.link_title, menu_links.link_path, menu_links.mlid, menu_links.plid, menu_links.weight, menu_node.mlid,
										node.nid, node.status, node.title, node.sticky, 
										node_counter.totalcount, url_alias.dst
						FROM node node  
						LEFT JOIN node_counter node_counter ON node.nid = node_counter.nid 
						LEFT JOIN menu_node ON node.nid = menu_node.nid
		        LEFT JOIN menu_links ON menu_node.mlid = menu_links.mlid
		        LEFT JOIN url_alias ON menu_links.link_path = url_alias.src
						WHERE (node.type in ('answer', 'answer_nc')) AND (node.status = 1 OR node.status is NULL) AND (menu_links.p1 = ".$mlid.")
						ORDER BY node.promote DESC, node.sticky DESC, node.changed DESC LIMIT 0,".$limit;
	
	$result = _db_query($query);
	$i = 1;

	echo '<ol>'."\n";

	global $user;
	if ($user->uid && !in_array('viewer',$user->roles)) {
	
		while ($row = db_result_assoc($result)){
			echo '				<li class="item'.$i.'"><a href="'.$row['link_path'].'/edit">'.$row['title'].'</a></li>'."\n";
			$i++;
		}  	

	}else {

		while ($row = db_result_assoc($result)){
			echo '				<li class="item'.$i.'"><a href="'.$row['link_path'].'">'.$row['title'].'</a></li>'."\n";
			$i++;
		}  	

	}

	echo '</ol>'."\n";
}



/*
function rating2xls($limit = 10000){
	$query = "SELECT node.nid AS nid, users.name AS users_name, users.uid AS users_uid, node.title AS node_title, node.language AS node_language, node.created AS node_created, votingapi_cache_node_percent_vote_average.value AS votingapi_cache_node_percent_vote_average_value 
						FROM node node  
						LEFT JOIN votingapi_cache votingapi_cache_node_percent_vote_average ON node.nid = votingapi_cache_node_percent_vote_average.content_id AND (votingapi_cache_node_percent_vote_average.content_type = 'node' AND votingapi_cache_node_percent_vote_average.value_type = 'percent' AND votingapi_cache_node_percent_vote_average.tag = 'vote' AND votingapi_cache_node_percent_vote_average.function = 'average') 
						INNER JOIN users users ON node.uid = users.uid 
						WHERE node.status <> 0 
						ORDER BY votingapi_cache_node_percent_vote_average_value DESC
						LIMIT 0,".$limit;
	
	$result = _db_query($query);
	$i = 1;

	global $user;
	if ($user->uid && !in_array('viewer',$user->roles)) {

		$ob_file = fopen('extraction.xls','w');
		ob_start('ob_file_callback');
	
#		for ($i = 0; $i < $fields; $i++) { 
#	    $header .= mysql_field_name($export, $i) . "\t"; 
#		}

		while ($row = db_result_assoc($result)){
	    $line = ''; 
	    foreach($row as $value) {                                             
	        if ((!isset($value)) OR ($value == "")) { 
	            $value = "\t"; 
	        } else { 
	            $value = str_replace('"', '""', $value); 
	            $value = '"' . $value . '"' . "\t"; 
	        } 
	        $line .= $value; 
	    } 
	    $data .= trim($line)."\n"; 
			$i++;
		}
		$data = str_replace("\r","",$data); 

		if ($data == "") { 
	    $data = "\n(0) Records Found!\n";                         
		}
		
		header("Content-type: application/x-msdownload"); 
		header("Content-Disposition: attachment; filename=extraction.xls"); 
		header("Pragma: no-cache"); 
		header("Expires: 0"); 
		print "$header\n$data";  

		ob_end_flush();

	} // end check user rights
}
*/
?>