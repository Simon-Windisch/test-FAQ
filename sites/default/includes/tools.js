function openPopup(url, width, height) {
	var win = window.open(url, 'Maxdome', 'width='+width+',height='+height);
	win.focus();
}

function openPopUpWindow( side, width, height, top, left, scrollbars ){
    if (side && side != null){
        var win = document.open(side, "_blank", "width=" + width + ",height=" + height + ",top="+ top + ",left=" + left + ",toolbar=no,status=no,location=no,menubar=no,directories=no,resizable=yes,scrollbars=" + scrollbars + ",scrolling=");
				win.focus();
    }
    return;
}



/*	Replace outgoing Links 
		based on CLCP v2.1 by Jonathan Snook */

if(window.location.href.search(/1und1/) != -1){
	var hostAdress = "1und1";	
}
var is_chrome = /chrome/.test( navigator.userAgent.toLowerCase() );
var is_safari = /webkit/.test( navigator.userAgent.toLowerCase() );

function replaceLinks(){
	var a = document.getElementsByTagName("A");
	
	for(var i=0; i < a.length; i++){
		// Links mit rel="portal" versuchen in mutterfenster zu oeffnen und ggf url ersetzen
		if(a[i].getAttribute("rel") == "portal"){
			
			// wenn maxdome ueber 1und1 geoeffnet, domain für weiterleitung korrigieren
			if(hostAdress == "1und1")
				if(a[i].href.search(/www\.maxdome/))
					a[i].href = a[i].href.replace(/www\.maxdome/, "maxdome.1und1");
		
			// wenn faq aus mutterfenster heraus geoeffnet wurden und dieses noch offen ist, link in mutterfenster oeffnen
			// in chrome und safari direkt in neuem fenster oeffnen, weil bug verweis in mutterfenster berhindert
			if (window.opener && !window.opener.closed && !is_chrome && !is_safari){
			//if (window.opener && !window.opener.closed){
				a[i].onclick = function(){
					opener.location.href = this.href;
					opener.focus(); return false;
				}
			}else{
				a[i].onclick = function(){
					Portal_window = window.open(this.href, "_blank", "height=680,width=1024,top=100,left=200,toolbar=yes,status=yes,location=yes,menubar=yes,directories=no,resizable=yes,scrollbars=yes,scrolling=yes"); return false;
  				Portal_window.focus();
				}
			}
			
		}
		// Links mit rel="external" in popup oeffnen
		else if(a[i].getAttribute("rel") == "external"){
				a[i].onclick = function(){
					External = window.open(this.href, "External", "height=680,width=1024,top=100,left=200,toolbar=yes,status=yes,location=yes,menubar=yes,directories=no,resizable=yes,scrollbars=yes,scrolling=yes"); return false;
  				External.focus();
				}
		} 
	}
}

window.onload = replaceLinks;

$(document).ready(function() {
	//Assign default value to form field #1
	$("#edit-search-block-form-1").DefaultValue("Suche in maxdome Hilfe");
});