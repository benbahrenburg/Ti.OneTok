/**
 *
 * Ti.OneTok Project
 * Copyright (c) 2009-2012 by Ben Bahrenburg. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 *
 **/
package ti.onetok;

import java.util.HashMap;
import org.appcelerator.kroll.KrollDict;
import org.appcelerator.kroll.KrollFunction;
import org.appcelerator.kroll.KrollProxy;
import org.appcelerator.kroll.annotations.Kroll;
import org.appcelerator.kroll.common.Log;
import org.appcelerator.titanium.TiApplication;
import com.onetok.sdk.AnalysisResult;
import com.onetok.sdk.OneTok;
import com.onetok.sdk.OneTokEventsListener;
import com.onetok.sdk.exceptions.OneTokException;
import com.onetok.sdk.network.NetworkContext;
import com.onetok.sdk.util.PreferencesManager;
import android.app.Activity;


@Kroll.proxy(creatableInModule=TionetokModule.class)
public class SessionProxy extends KrollProxy implements OneTokEventsListener{
	private OneTok _mOneTok;
	private String _serviceStatus ="Unknown";
	private KrollFunction loginSuccessCallback = null;
	private KrollFunction loginFailCallback = null;
	private KrollFunction resultsCallback = null;
	private KrollFunction errorCallback = null;
	private KrollFunction onFinishCallback = null;
	private boolean _displayInConsule= false;
	// Standard Debugging variables
	private static final String LCAT = "TionetokModule";
	
	enum ServiceStatus {
		NotAuthenticated, Authenticating, Authenticated, Recording, Iddle
	}

	ServiceStatus _status = ServiceStatus.NotAuthenticated;

	private void doLog(String msg,boolean forceLog){
		if((_displayInConsule)||(forceLog)){
			Log.i(LCAT, msg);
		}
	}
	
	public SessionProxy() 
	{
		super();
		doLog("init with proxy id of " + getProxyId(),false);
	}
	

	@Override
	public void onAuthenticationSuccess() {
		doLog("On authentication success",false);
		setStatus(ServiceStatus.Authenticated);
		if(loginSuccessCallback!=null){
			doLog("starting callback loginSuccessCallback",false);
    		HashMap<String, Object> event = new HashMap<String, Object>();
			event.put("success",true);
			loginSuccessCallback.call(getKrollObject(), event);			
		}
	}

	@Override
	public void onRecordingFinished() {
		doLog("Stopped recording: " + System.currentTimeMillis(),false);
		setStatus(ServiceStatus.Iddle);
		if(onFinishCallback!=null){
    		HashMap<String, Object> event = new HashMap<String, Object>();
			event.put("message","Recording finished");
			event.put("success",true);
			onFinishCallback.call(getKrollObject(), event);
		}
	}

	@Override
	public void onError(final OneTokException exception) {
		doLog("On error: " + exception.getMessage(),true);
		
		if(_status==ServiceStatus.Authenticating){
			if(loginFailCallback!=null){
	    		HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("success",false);
				event.put("message", exception.getMessage());
				loginFailCallback.call(getKrollObject(), event);					
			}
		}
		else
		{
			if(errorCallback!=null){
	    		HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("success",false);
				event.put("message", exception.getMessage());
				errorCallback.call(getKrollObject(), event);					
			}
		}
	
		if (_mOneTok != null) {
			_mOneTok.stopRecording();
		}
	}

	private String ResultType(AnalysisResult.ResultType value){
		String results = "none";
		
		if(value==AnalysisResult.ResultType.VALID ){
			results="valid";
		}
		if(value==AnalysisResult.ResultType.EMPTY ){
			results="literal";
		}
		return results;
	}
	
	@Override
	public void onAnalysisProcessingResult(final AnalysisResult result) {
        if (resultsCallback!=null){ 
        	doLog("Providing results to callback",false);
    		HashMap<String, Object> event = new HashMap<String, Object>();
			event.put("session_id",result.getSessionId());
			event.put("success",true);
			event.put("result",result.getAnalysisResultText());
			event.put("analysis_status",result.getStatus().isPendingStatus() ? "pending" : ( result.getStatus() == AnalysisResult.Status.FINALIZED ?  "finalized" : (  result.getStatus() == AnalysisResult.Status.FINALIZED_WITH_ERROR_MAXIMUM_RETRIES ? "error max retries" : "error" )));
			event.put("result_type",ResultType(result.getAnalysisResultType()));
			resultsCallback.call(getKrollObject(), event);
        }
	}

	private void setStatus(ServiceStatus newStatus) {

		switch (newStatus) 
		{
			case NotAuthenticated:
				_serviceStatus = "Not Authenticated";
				break;
			case Authenticating:
				_serviceStatus= "Authenticating";
				break;
			case Authenticated:
				_serviceStatus="Authenticated";
				break;
			case Iddle:
				_serviceStatus="Iddle";
				break;
			case Recording:
				_serviceStatus ="Recording";
				break;
		}		
		_status = newStatus;
		doLog("Statuns changed: " + _serviceStatus,false);
	}

	@Kroll.method
	public void showInConsole(Boolean showInConsole)
	{
		_displayInConsule=showInConsole;
	}
	@Kroll.method
	public void authenticate(@SuppressWarnings("rawtypes") HashMap hm)
	{	
		@SuppressWarnings("unchecked")
		KrollDict args = new KrollDict(hm);
		String hostName = args.getString("hostName");
		doLog("hostName: " + hostName,false);
		String appID = args.getString("appID");
		doLog("appID: " + appID,false);
		String appToken = args.getString("appToken");
		doLog("appToken: " + appToken,false);
		//String version = args.optString("version","");
		boolean UseSpeex = args.optBoolean("useSpeex", false);

		Object onSuccess = args.get("onSuccess");
		if (onSuccess instanceof KrollFunction) {
			loginSuccessCallback = (KrollFunction)onSuccess;
		}

		Object onError = args.get("onError");
		if (onError instanceof KrollFunction) {
			loginFailCallback = (KrollFunction)onError;
		}
		
		setStatus(ServiceStatus.NotAuthenticated);
		
		NetworkContext ctx = new NetworkContext(appID,appToken);
		
		if (ctx != null) {
			if (UseSpeex) {
				ctx.getPreferences().setDesiredCodec(PreferencesManager.Codec.CODEC_SPEEX);
			}
			setStatus(ServiceStatus.Authenticating);			
			_mOneTok = new OneTok(TiApplication.getInstance().getCurrentActivity(), ctx,SessionProxy.this);
		}
	}

	@Kroll.method
	public void startRecording(@SuppressWarnings("rawtypes") HashMap args){

		Object onResults = args.get("onResults");
		if (onResults instanceof KrollFunction) {
			resultsCallback = (KrollFunction)onResults;
		}

		Object onError = args.get("onError");
		if (onError instanceof KrollFunction) {
			errorCallback = (KrollFunction)onError;
		}	
		Object onFinish = args.get("onFinish");
		if (onFinish instanceof KrollFunction) {
			onFinishCallback = (KrollFunction)onFinish;
		}			
		
		if (_mOneTok != null) {
			if((_status == ServiceStatus.Authenticated) || 
					(_status == ServiceStatus.Iddle)){
				setStatus(ServiceStatus.Recording);
				doLog("Starting to record",false);
				_mOneTok.startRecordingIndefinitely(null);				
			}
		}
	}

	@Kroll.method
	public void stopRecording(@SuppressWarnings("rawtypes") HashMap args){
		if (_mOneTok != null) {
			_mOneTok.stopRecording();
		}	
		doLog("Recording Stopped",false);
	}

	public void onDestroy(Activity activity) 
	{
		// This method is called when the root context is being destroyed
		if (_mOneTok != null) {
			_mOneTok.dispose();
		}
		if(loginSuccessCallback!=null){
			loginSuccessCallback=null;
		}
		if(loginFailCallback!=null){
			loginFailCallback=null;
		}
		if(resultsCallback!=null){
			resultsCallback=null;
		}
		if(errorCallback!=null){
			errorCallback=null;
		}
		if(onFinishCallback!=null){
			onFinishCallback=null;
		}
	}

	@Override
	public void onCreateRecognizerSuccess() {
		// TODO Auto-generated method stub
		
	}
}