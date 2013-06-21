<?php
	($_GET[w]) ? $width = $_GET[w] : $width = 1024;
	($_GET[h]) ? $height = $_GET[h] : $height = 576;
	($_GET[title]) ? $title = $_GET[title] : $title = '';
	($_GET[vsrc]) ? $vsrc = $_GET[vsrc] : $error = TRUE;
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
    <head>
        <title></title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script src="assets/jquery-1.4.2.js"></script>
        <script src="assets/joose.js"></script>
        <script src="assets/jquery-external_interface.js"></script>
        <script src="assets/swfobject.js"></script>
        <script src="assets/flexPlayer.js"></script>
    </head>
    <body>
<?php
if($error != TRUE){
?>    	
        <div id="player" style="display: block; width: <?php echo $width; ?>px; height: <?php echo $height; ?>px;"></div>
        <script type="text/javascript">
            var playerNode = $('#player');

            var player = new flexPlayer(
                playerNode,
                'maxdome',
                '<?php echo $title; ?>',
                '<?php echo $vsrc; ?>',
                {
                    width: '<?php echo $width; ?>',
                    height: '<?php echo $height; ?>',
                    autoplay: 1,
                    playerDirectory: 'assets/'
                }
            );
        </script>
<?php
}else{
?>	
        <div id="message" style="display: block; width: <?php echo $width; ?>px; height: <?php echo $height; ?>px;">Videospur kann nicht geladen werden.</div>
<?php	
}
?>
    </body>
</html>