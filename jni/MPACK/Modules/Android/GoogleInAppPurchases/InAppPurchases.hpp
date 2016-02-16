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

				const static int BINDING = 1;
				const static int BINDING_ERROR = 2;
				const static int BINDING_DONE = 3;

				const static int NO_PROCESS = 4;
				const static int PROCESSING = 5;
				const static int SUCCESS = 6;
				const static int PURCHASE_CANCELED = 7;
				const static int PURCHASE_ERROR = 8;
				const static int CONSUME_ERROR = 9;
				const static int CONSUMING_QUERY = 10;

				const static int NO_TYPE = 11;
				const static int PURCHASE_TYPE = 12;
				const static int SUBSCRIPTION_TYPE = 13;

				const static int QUERYING = 14;
				const static int QUERY_FINISHED = 15;
				const static int QUERY_CONSUMING = 16;
				const static int QUERY_ERROR = 17;
				const static int QUERY_PRICE_FINISHED = 18;
				const static int QUERYING_PRICE = 19;

				ANativeActivity* mActivity;
				JavaVM* mJvm;
				bool mLoadedPrices;
				bool mConsumed;
				vector<pair<string, string>> mPrices;

			public:
				InAppPurchases();
				~InAppPurchases();
				void bindServices();

				int getServiceBindingState();

				void purchase(const string purchase_id, const string developerPayload);
				void subscribe(const string purchase_id, const string developerPayload);
				int getCurrentProcessState();
				int getCurrentProcessType();

				bool isQueried();
				bool isPriceQueried();

				int getCurrentQueryProcessState();
				void startQuery();
				void startPriceQuery(const vector<string> &);
				vector<string> getConsumedItems();
				vector<pair<string,string> > getAllPrices();

				void consumeAllPurchases(const string developerPayLoad);
			private:
				void callMainActivityJavaFunction(const char * );
				int callInAppPurchasesIntJavaFunctionWithoutParams(const char *);
				bool callInAppPurchasesBoolJavaFunctionWithoutParams(const char *);
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

