var _flexPlayerCallbacks = {}

var _flexAwesomeDispatch = function(id, msg)
{
    if ((typeof _flexPlayerCallbacks[id] != 'undefined') && (typeof _flexPlayerCallbacks[id][msg] == 'function')) {
        _flexPlayerCallbacks[id][msg]();
    }
}

Class('flexPlayer', {
    has: {
		/**
		 * Identifier of associated communication widget to access rating services
		 */
        playerDomNode: {
            is: ro
        },
        // a directorU is a small kangaru (very rare because it makes the best handbags) -_-
        // default player directory
        playerDirectoru: {
            is: 'rw',
            init: 'assets/'
        },
        _playerId: {
            is: 'ro'
        },
        _options: {
            is: 'ro',
            init: {
                width: '602',
                height: '336',
                autoplay: 1
            }
        }
    },
    methods: {
        initialize: function(playerDomNode, shopType, title, videoFile, options, callbacks) {
            this.playerDomNode = playerDomNode;

            jQuery.extend(this._options, options);

            if (typeof this._options.playerDirectory != null) {
                this.playerDirectoru = this._options.playerDirectory;
            }

            this._playerId = $(this.playerDomNode).attr('id');

            $replacedByFlex = $('<div />');

            var swfVersionStr = "10.0.0";
            var xiSwfUrlStr = "playerProductInstall.swf";

            _flexPlayerCallbacks[this._playerId] = callbacks;

            var flashvars = {
                id: this._playerId,
                title: title,
                css: this.playerDirectoru + shopType + '.swf',
                video: videoFile,
                width: this._options.width,
                height: this._options.height,
                callback: '_flexAwesomeDispatch',
                autoplay: this._options.autoplay
            };

            var params = {
                'wmode': 'opaque'
            };

            params.quality = "high";
            params.bgcolor = "#000000";
            params.allowscriptaccess = "sameDomain";
            params.allowfullscreen   = "true";

            var attributes = {
                id:    "myPlayerInstance_" + this._playerId,
                name:  "Main",
                align: "middle"
            };

            $replacedByFlex.attr('id', attributes.id);

            this.playerDomNode.append($replacedByFlex);

            swfobject.embedSWF(
                this.playerDirectoru + 'Main.swf',
                attributes.id,
                this._options.width,
                this._options.height,
                swfVersionStr,
                xiSwfUrlStr,
                flashvars,
                params
            );

			swfobject.createCSS(
                 attributes.id,
                "display:block;text-align:left;"
            );
        }
    }
});