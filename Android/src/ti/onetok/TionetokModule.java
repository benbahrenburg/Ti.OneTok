/**
 *
 * Ti.OneTok Project
 * Copyright (c) 2009-2012 by Ben Bahrenburg. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 *
 **/
package ti.onetok;
import org.appcelerator.kroll.KrollModule;
import org.appcelerator.kroll.annotations.Kroll;
import org.appcelerator.titanium.TiApplication;
import org.appcelerator.kroll.common.Log;


@Kroll.module(name="Tionetok", id="ti.onetok")
public class TionetokModule extends KrollModule
{
	// Standard Debugging variables
	private static final String LCAT = "TionetokModule";

	public TionetokModule()
	{
		super();
	}

	@Kroll.onAppCreate
	public static void onAppCreate(TiApplication app)
	{
		Log.d(LCAT, "Module Started");
	}

}

