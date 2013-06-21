			$(function() {
				// hide sections (between 2 and 4)
				for(var i = 2; i <= 4; i++)	{
					document.getElementById('section-' + i).style.display = 'none';
				}
			});


			// loop sections automatically
			var stage_interval = window.setInterval("auto_switch()", 5000);
			var steps = 0, section = 1;
			function auto_switch() {
			  if (section <= 3) {
			    switch_section(section);
			    section = section +1;
			  } else {
			    switch_section(section);
			    section = 1;
			  }
				// stop loop after 13 steps
			  steps = steps + 1;
			  if (steps >= 13)
			    window.clearInterval(stage_interval);
			}

			//switch sections on demand
			function tab_switch(id)	{
				window.clearInterval(stage_interval);
				switch_section(id);
			}


			//switch sections
			var lastTabId = 1;
			function switch_section(id)	{
				document.getElementById('section-' + lastTabId).style.display = 'none';
				document.getElementById('section-' + id).style.display = 'block';
				sIFR.replace(sitesdefaultfilesrenderhelveticaNeue_boldExt_sifr3swf, { "font": "/sites/default/files/render/helveticaNeue_boldExt_sifr3.swf", "selector": ".front #stage h2", "css": { ".sIFR-root": { "display": "block", "font-size": "22px", "font-weight": "normal", "font-style": "normal", "color": "#f1f1f1", "background-color": "", "margin-left": 0, "margin-right": 0, "text-align": "left", "text-indent": 0, "text-transform": "uppercase", "text-decoration": "none", "letter-spacing": 0, "opacity": "100", "leading": 0, "kerning": "false", "cursor": "arrow" }, "a": { "text-decoration": "none" }, "a:link": { "color": "#f1f1f1" }, "a:hover": { "color": "#f1f1f1", "text-decoration": "none" } }, "wmode": "transparent", "fontname": "sitesdefaultfilesrenderhelveticaNeue_boldExt_sifr3swf" });
				lastTabId = id;
				
				var anchorlist = document.getElementById('tab_anchors');
				var ourTabs = document.getElementById('tab_anchors').getElementsByTagName("li");
				
				for(var i = 0; i < ourTabs.length; i++)	{
					if ((i + 1) == id) {
						anchorlist.className = 'state' + (i+1);
						ourTabs[i].className = 'active';
						//ourTabs[i].className = 'active tab' + (i+1);
					}
					else {
						ourTabs[i].className = '';
						//ourTabs[i].className = 'tab' + (i+1);
					}
				}
			}
