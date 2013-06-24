<?php
	if(strpos($body_classes, "node-type-answer")){
		$node_typestyle = "answer";
	
		# Variablen für Suchergebnis-verknuepfung 
		if($_SERVER['HTTP_REFERER'] && strpos($_SERVER['HTTP_REFERER'], "/search/node/")){
			$title = ($_SERVER['HTTP_REFERER'] && strpos($_SERVER['HTTP_REFERER'], "search")) ? "Suche" : "Antwort";
			$breadcrumb = '<div class="breadcrumb"><a href="/">Hilfe</a> > <a href="/search">Suche</a> > <a href="'.$_SERVER['HTTP_REFERER'].'">Suchergebnis</a> > Antwort</div>';
		}
	}
?>
<!DOCTYPE	html PUBLIC	"-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
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

	<body	class="<?php print $body_classes;	?>">
		
		<div id="skip-nav"><a	href="#content">Skip to	Content</a></div>	 

	<!-- ______________________	HEADER _______________________ -->

		<div id="header">
			<div id="header-inner">
				<div id="header-nav--meta">
					<ul>
						<li>
							<a href="http://www.maxdome.de/" class="arrow-right">maxdome</a>
						</li>
					</ul>
				</div>
				<div id="logo">
	<?php	if (!empty($site_name)): ?>
						<h1	id="site-name"><a href="<?php	echo	$front_page	?>"	title="<?php echo	t('Home'); ?>" rel="home"><span><?php	echo $site_name; ?></span></a></h1>
	<?php	endif; ?>
				</div>
				<div id="web-presence-part">FAQ</div>
			
	<?php	if ($header):	?>
				<div id="header-region">
					<?php	echo $header;	?>
				</div>
	<?php	endif; ?>
	
			</div> <!--	/header-inner -->
		</div> <!--	/header	-->

	<!-- ______________________	PAGE _______________________ -->


		<div id="page">

		<!-- ______________________	MAIN _______________________ -->

		<?php	print	$messages; ?>

		<div id="main" class="clearfix">
<?php	if ($breadcrumb):	?>
			<?php	echo $breadcrumb;	?>
<?php	endif; ?>
		
			<div id="content">
				<div id="content-inner"	class="inner column	center">
					
					<?php	if ($title	|| $messages ||	$help	|| $tabs): ?>
						<div id="content-header">

							<?php	if ($title): ?>
								<div id="title-wrapper"><h1	class="title"><?php	print	$title;	?></h1></div>
							<?php	endif; ?>

							<?php	if ($mission): ?>
								<div id="mission"><?php	print	$mission;	?></div>
							<?php	endif; ?>

							<?php	if ($tabs):	?>
								<div class="tabs"><?php	print	$tabs; ?></div>
							<?php	endif; ?>

							<?php	if ($help):	?>
								<?php	print	$help; ?>
							<?php	endif; ?>

						</div> <!--	/#content-header -->
					<?php	endif; ?>

					<?php	if ($page_top):	?>
						<div id="content-top">
							<?php	print	$page_top; ?>
						</div> <!--	/#content-top	-->
					<?php	endif; ?>

					<div id="content-area">
						<?php	print	$content;	?>
					</div> <!--	/#content-area -->

					<?php	print	$feed_icons; ?>

					<?php	if ($page_bottom): ?>
						<div id="content-bottom">
							<?php	print	$page_bottom;	?>
						</div><!-- /#content-bottom	-->
					<?php	endif; ?>

					</div>
				</div> <!--	/content-inner /content	-->


				<?php	if ($left):	?>
					<div id="sidebar-first"	class="column	sidebar	first">
						<div id="sidebar-first-inner"	class="inner">
							<?php	print	$left; ?>
						</div>
					</div>
				<?php	endif; ?>	<!-- /sidebar-left -->

				<?php	if ($right): ?>
					<div id="sidebar-second" class="column sidebar second">
						<div id="sidebar-second-inner" class="inner">
							<?php	print	$right;	?>
						</div>
					</div>
				<?php	endif; ?>	<!-- /sidebar-second -->

			</div> <!--	/main	-->
			
			<!-- Error-Message for IE6 -->
			<div id="ie6"><h1>Es tut uns leid.</h1><p>Diese Seite wird von Ihrer Browser-Version nicht unterstützt.</p><p>Unter folgendem Link können Sie die aktuelle Version kostenlos herunterladen:<br/><a href="http://www.microsoft.com/germany/windows/internet-explorer/">Internet-Explorer Download</a></p></div>
			
			<!-- ______________________	FOOTER _______________________ -->

				<div id="footer">
					<?php	print	$footer_message; ?>
					<?php	print	$footer; ?>
				</div> <!--	/footer	-->

		</div> <!--	/page	-->
		<?php	print	$closure;	?>
	</body>
</html>