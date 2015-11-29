(function() {
  var app = angular.module("app", []);
  
  app.controller("HttpCtrl", function($scope, $http) {
    
	var app = this;
	app.tvAnswer='off';
	app.airAnswer='off';
	app.netAnswer='off';
	app.tvLoadAnswer='notShowTVLoading';
	app.airLoadAnswer='notShowAIRLoading';
	app.netLoadAnswer='notShowNETLoading';
	app.tvAction = 'Turn On';
	app.airAction = 'Turn On';
	app.netAction = 'Turn On';
	app.tvLoadError='notShowTVError';
	
        $scope.getActor = function(id) {
    	
        //alert(id);
    	$http.defaults.useXDomain = true;
    	$http.defaults.headers.common['X-Requested-With'];
    	//TV == 3
    	if (id == 3){
    		app.tvLoadAnswer='showTVLoading';
    		$http({method: 'GET', url: '/HouseAutometions/rest/device/3'}).
    			success(function(data, status, headers, config) {
            
    				app.tvLoadAnswer='notShowTVLoading';
    				app.tvLoadError='notShowTVError';
					//As IR command its the same for on and off
    				if (app.tvAnswer == 'on'){
						app.tvAnswer = 'off';
						app.tvAction = 'Turn On';
					}else{
						app.tvAnswer = 'on';
						app.tvAction = 'Turn Off';
					}

    			}).
    			error(function(data, status, headers, config) {
    					app.tvLoadAnswer='notShowTVLoading';
    					app.tvLoadError='showTVError';
    					
    			});
    	}
    	//Air == 6
    	if (id == 6){
    		app.airLoadAnswer='showAIRLoading';
    		$http({method: 'GET', url: '/HouseAutometions/rest/device/6'}).
    			success(function(data, status, headers, config) {
					//As IR command its the same for on and off
    				app.airLoadAnswer='notShowAIRLoading';
					if (app.airAnswer == 'on'){
						app.airAnswer = 'off';
						app.airAction = 'Turn On';
					}else{
						app.airAnswer = 'on';
						app.airAction = 'Turn Off';
					}

    			}).
    			error(function(data, status, headers, config) {
    					app.airLoadAnswer='notShowAIRLoading';

        	 
    			});
    	}
    	//NET = 2
    	if (id == 2){
    		app.netLoadAnswer='showNETLoading';
    		$http({method: 'GET', url: '/HouseAutometions/rest/device/2'}).
    			success(function(data, status, headers, config) {
					//As IR command its the same for on and off
    				app.netLoadAnswer='notShowNETLoading';
    				app.netAnswer='on';
 					if (app.netAnswer == 'on'){
						app.netAnswer = 'off';
						app.netAction = 'Turn On';
					}else{
						app.netAnswer = 'on';
						app.netAction = 'Turn Off';
					}

    			}).
    			error(function(data, status, headers, config) {
    					app.netLoadAnswer='notShowNETLoading';
        	 
    			});
    	}	


    	
    	
    };
     
  }); 
})();



