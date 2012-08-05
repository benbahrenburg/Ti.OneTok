<h1>Ti.OneTok for iOS</h1>
 
Welcome to the OneTok iOS Titanium module project.

This project provides iOS Titanium access to the OneTok SDK.

<h2>About OneTok</h2>
OneTok provides developers with a simple and flexible infrastructure for building voice recognition controls into mobile apps.

The OneTok SDK has been developed as part of the OneTok Voice Platform to provide to mobile app developers a simple and easy way to add voice controls to their mobile apps. The OneTok SDK consists of a native library for iOS, Android (Blackberry and Windows Phone) as well as a series of web accessible, network-based services including voice recognition, grammars and natural language processing.

<h2>Getting Started With OneTok</h2>
	
* Create a developer account on [Onetok.com](http//Onetok.com)
* Create a new app
* Add an App Name
* Select an App Category, which will associate the app with a selection of pre-defined methods and sample sentences (e.g. for the banking category this will include methods such as getBalance, findAtm, findBranch, showTransactions and transferFunds and all of their corresponding sample sentences).

Once your app has been created OneTok will generate an App ID and App Token that the developer will use to uniquely identify their app when interacting with the OneTok API.
	
Your App Keys are then provided the Ti.OneTok's authentication method.
	
<h2>OneTok Documentation</h2>

The OneTok SDK is fully documented and includes sample code.  Please visit their [documentation library for details](http://sandbox.onetok.com:8080/li/documentation.jsf).

<h2>Before you start using the Module</h2>
* You need a OneTok account, see about for details
* You need Titanium 1.8.2 or greater.
* This module will only work with iOS 4.2 or great.  

<h2>Module Setup</h2>

* Download the latest release from the [dist folder](https://github.com/benbahrenburg/Ti.OneTok/tree/master/iOS/dist) or you can build it yourself 
* Install the bencoding.map module. If you need help here is a "How To" [guide](https://wiki.appcelerator.org/display/guides/Configuring+Apps+to+Use+Modules). 
* You can now use the module via the commonJS require method, example shown below.

<pre><code>
//Add the module into your project
var oneTok = require('ti.onetok');

</code></pre>

Now we have the module installed and avoid in our project we can start to use the components, see below for details.

<h2>Using Ti.OneTok</h2>

<h3>Creating a Session</h3>
After adding the OneTok module into your tiapp.xml and placing the proper require statement as shown about, you next need to create a Session.

The Ti.OneTok Session object contains all of the OneTok methods and listeners.

<pre><code>
//Create a new session object
var oneTokSession = oneTok.createSession();
</code></pre>

<h3>Authenticating your session</h3>
Before you can start using Ti.OneTok you first need to authenticate. This tells OneTok which App, App Category, and Grammars you wish to use.

It is important to note that all OneTok methods require a network connection. Please make sure to add a Ti.Network.online check before calling any Ti.OneTok Session methods.

The authenticate method takes a dictionary with the following properties:
* hostName - The OneTok API string, this currently is http://sandbox.onetok.com:8080
* appID  - Your App ID created as part of the OneTok App creation process
* appToken - Your App token created as part of the OneTok App creation process
* version - version of the OneTok API used
* onSuccess - Callback method triggered when authentication is successful
* onError - Callback method triggered when an error happens during authentication

<pre><code>

//Sample demonstrating how to authenticate a Ti.OneTok Session
function authenticateSession(){
	
	function onError(e){
		//We encountered an error, provide the details
		Ti.API.info(e);
		alert('Errored on Authentication');
	};
	function onSuccess(e){
		//Login was successful
		alert('Authenticated Successfully');
	};
	
	if(!Ti.Network.online){
		alert("I'm sorry a network connection is needed to use this module");
	}else{
		oneTokSession.authenticate({
				hostName:"http://sandbox.onetok.com:8080",
				appID : "YOUR_APP_ID_GOES_HERE",
				appToken : "YOUR_APP_TOKEN_GOES_HERE",
				version : "0.1",
				onSuccess:onSuccess, //Called when authentication is successful
				onError:onError //Called on authentication error		
		});		
	}	
};

</code></pre>

<h3>Start Recording</h3>

<pre><code>

function startRecording(){
	var oneTokOutput = [];
	
	//This method is called on error
	function onError(e){
		Ti.API.info(e);
		alert('Errored while recording');
	};
	
	//This method is called as OneTok processes your
	//speak results. This will be called several times before finish
	function onResults(e){
		Ti.API.info("results=" + JSON.stringify(e));
		//We add the pending results to be used later.
		oneTokOutput.push(e);
		//You can check the result_type to determine if 
		//a valid result has been returned
		if(e.result_type=='valid'){
			Ti.API.info("Valid Results=" + JSON.stringify(e));	
		}
	};
	
	//This method is called when the recording session has finished
	function onFinish(e){
		alert('Recording Completed');
		Ti.API.info(JSON.stringify(oneTokOutput));
	};
	
	if(!Ti.Network.online){
		alert("I'm sorry a network connection is needed to use this module");
	}else{		
		oneTokSession.startRecording({
				onResults:onResults, //Add callback to process results, called many times 
				onError:onError, //Add callback to handle error messages
				onFinish:onFinish  //Add callback to handle when recording has finished
		});
	}	
};

</code></pre>
<h3>Stop Recording</h3>

To Stop the recording process call the stopRecording method on the Ti.OneTok Session object as shown below.

<pre><code>

//Stop Recording
oneTokSession.stopRecording();

</code></pre>

<h3>Finding the current Session Status</h3>

You can find the current Ti.OneTok Session status by calling the currentStatus method as shown below.

<pre><code>

//Find current OneTok Session Status
var foo = oneTokSession.currentStatus();
Ti.API.info("Current Status is " + foo);
alert("Current Status is " + foo);

</code></pre>

The currentStatus method returns a string with the one of the below values:
* Unknown
* Not Authenticated
* Authenticating
* Authenticated
* Iddle
* Recording
* Waiting For Results

<h2>Examples</h2>

A fully working sample app.js is available in the module's example folder or for download [here](https://github.com/benbahrenburg/Ti.OneTok/tree/master/iOS/example).

<h2>FAQ</h2>

* Is there an Android version?  - Coming soon

<h2>Legal Stuff</h2>

Appcelerator is a registered trademark of Appcelerator, Inc. Appcelerator Titanium is a trademark of Appcelerator, Inc.

OneTok is a registered trademark of OneTok, Inc.

<h2>Licensing</h2>

The module specific code is covered under the OSI approved Apache Public License (version 2).  Titanium and OneTok SDKs are covered under their open licensing agreements. Please contact each vendor for details.

Please see the Titanium licensing located [here](https://github.com/appcelerator/titanium_mobile).

Please see the OneTok licensing on their website [here](http://onetok.com).

<h2>Contributing</h2>

The Ti.OneTok is a open source project.  Please help us by contributing to documentation, reporting bugs, forking the code to add features or make bug fixes or promoting on twitter, etc.

<h2>Learn More</h2>

<h3>Twitter</h3>

Please consider following the [@benCoding Twitter](http://www.twitter.com/benCoding) for updates and more about Titanium.

<h3>Blog</h3>

For module updates, Titanium tutorials and more please check out my blog at [benCoding.Com](http://benCoding.com). 
