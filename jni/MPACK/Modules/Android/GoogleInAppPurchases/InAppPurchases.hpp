#ifdef ANDROID_PLATFORM

#ifndef INAPPPURCHASES_H
#define INAPPPURCHASES_H

#include <jni.h>
#include <android_native_app_glue.h>
#include <string>
#include <vector>
using namespace std;

namespace MPACK
{
	namespace SERVICES
	{
		class InAppPurchases
		{
			public:
				static const string SEPARATOR;

				const static int BINDING = 0;
				const static int BINDING_ERROR = -1;
				const static int BINDING_DONE = 1;

				const static int NO_PROCESS = 0;
				const static int PROCESSING = 1;
				const static int SUCCESS = 2;
				const static int PURCHASE_CANCELED = 3;
				const static int PURCHASE_ERROR = -1;
				const static int CONSUME_ERROR = -2;
				const static int CONSUMING_QUERY = 4;

				const static int NO_TYPE = 0;
				const static int PURCHASE_TYPE = 1;
				const static int SUBSCRIPTION_TYPE = 2;

				const static int QUERYING = 1;
				const static int QUERY_FINISHED = 2;
				const static int QUERY_CONSUMING = 3;
				const static int QUERY_ERROR = -1;
				const static int QUERY_PRICE_FINISHED = 4;
				const static int QUERYING_PRICE = 5;

				ANativeActivity* mActivity;
				JavaVM* mJvm;

			public:
				InAppPurchases();
				void bindServices();
				void destroy();
				int getServiceBindingState();

				void purchase(const string purchase_id, const string developerPayload);
				void subscribe(const string purchase_id, const string developerPayload);
				int getCurrentProcessState();
				int getCurrentProcessType();

				int getCurrentQueryProcessState();
				void startQuery();
				void startPriceQuery(const vector<string> &);
				vector<string> getConsumedItems();
				vector<pair<string,string> > getAllPrices();

				void consumeAllPurchases(const string developerPayLoad);
			private:
				void callMainActivityJavaFunction(const char * );
				int callInAppPurchasesIntJavaFunctionWithoutParams(const char *);
				void callInAppPurchasesVoidJavaFunctionWithoutParams(const char *);
				void callInAppPurchasesVoidJavaFunctionString(const char * , const string);
				void callInAppPurchasesVoidJavaFunction2String(const char * , const string, const string);
				string callInAppPurchasesStringJavaFunctionWithoutParams(const char *);
				void callInAppPurchasesVoidJavaFunctionVectorString(const char *, const vector<string> &);
				vector<string> callInAppPurchasesVectorStringJavaFunctionWithoutParams(const char *);
		};

	}
}


#endif
#endif

