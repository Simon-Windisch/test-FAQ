<?php
// $Id: maintenance-page.tpl.php,v 1.2.2.1 2009/04/30 00:13:31 goba Exp $

/**
 * @file maintenance-page.tpl.php
 *
 * Theme implementation to display a single Drupal page while off-line.
 *
 * All the available variables are mirrored in page.tpl.php. Some may be left
 * blank but they are provided for consistency.
 *
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<!DOCTYPE	html PUBLIC	"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html	xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php	print	$language->dir ?>">

	<head>
		<title>maxdome - Hilfe <?php /* print $head_title;	*/ ?></title>
		<?php	print	$head; ?>
		<?php	print	$styles; ?>
		<!--[if	lte	IE 6]><style type="text/css" media="all">@import "<?php	print	$base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
		<!--[if	IE 7]><style type="text/css" media="all">@import "<?php	print	$base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->
		<!--[if	IE 8]><style type="text/css" media="all">@import "<?php	print	$base_path . path_to_theme() ?>/css/ie8.css";</style><![endif]-->
		<?php	print	$scripts;	?>
	</head>


	<body	class="<?php print $body_classes;	?> offline">
		<div id="page">

		<!-- ______________________	HEADER _______________________ -->

			<div id="header">
				<div id="header-inner">
					<div id="logo">
		<?php	if (!empty($site_name)): ?>
							<h1	id="site-name"><a href="<?php	echo	$front_page	?>"	title="<?php echo	t('Home'); ?>" rel="home"><span><?php	echo $site_name; ?></span></a></h1>
		<?php	endif; ?>
					</div>
					<div id="web-presence-part">FAQ</div>
				
				</div> <!--	/header-inner	-->
			</div> <!--	/header	-->

		<!-- ______________________	MAIN _______________________ -->

		<?php	print	$messages; ?>

      <div id="main" class="column">
      </div> <!-- /main -->
      
			<div id="offline">
				<h1><?php print $title; ?></h1>
				<p><?php print $content; ?></p>
			</div>

			<!-- Error-Message for IE6 -->
			<div id="ie6"><h1>Es tut uns leid.</h1><p>Diese Seite wird von Ihrer Browser-Version nicht unterstützt.</p><p>Unter folgendem Link können Sie die aktuelle Version kostenlos herunterladen:<br/><a href="http://www.microsoft.com/germany/windows/internet-explorer/">Internet-Explorer Download</a></p></div>

			<div id="footer">
				© maxdome GmbH & Co. KG - alle Rechte vorbehalten 
			</div> <!--	/footer	-->

		</div> <!--	/page	-->
		<?php	print	$closure;	?>
</body>
</html>