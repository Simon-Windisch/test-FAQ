<?php
	if(strpos($classes, "node-type-answer") || $classes == "node-type-answer") {
		$node_typestyle = "answer";

		# Variablen für Suchergebnis-verknuepfung 
		if($_SERVER['HTTP_REFERER'] && strpos($_SERVER['HTTP_REFERER'], "/search/node/")){
			$referer = "search";
		}
	}


?>
<div class="node <?php echo $classes; ?>" id="node-<?php echo $node->nid; ?>">
	<div class="node-inner">
    
    <?php if (!$page): ?>
      <h2 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
        
    <?php if ($node_typestyle == "answer"): ?>
	  	<!-- <h4 class="title node-title"><?php echo $title; ?></h4> -->
	  	<h3 class="title node-title">Antwort</h3>
		<?php endif; ?>
    
    <?php print $user_picture; ?>
    		    
    <?php if ($submitted && $node_typestyle != "answer"): ?>
      <!--<span class="submitted"><?php echo $submitted; ?></span>-->
    <?php endif; ?>

    <div class="content">
      <?php print $content; ?>
    </div>

		<?php if($referer == "search"): ?>
			<hr style="clear:both;" />
	  	<a href="<?php echo $_SERVER['HTTP_REFERER']; ?>" class="pagelink prom">zur&uuml;ck zu den anderen Suchtreffern</a>
  	<?php endif;?>
  	
    <?php if ($terms): ?>
      <div class="taxonomy"><?php print $terms; ?></div>
    <?php endif;?>
    
    <?php if ($links): ?> 
	    <div class="links"> <?php echo $links; ?></div>
	  <?php endif; ?>
    
	</div> <!-- /node-inner -->
</div> <!-- /node-->