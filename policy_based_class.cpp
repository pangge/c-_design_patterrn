#include "policy_base_class.h"

/** 
 * @brief test for policy
 */
class Widget{
public:
	Widget(){
		printf("<!-- Widget construct !  ... ");
	}
	~Widget(){
		printf("  Widget deconstruct  -->\n");
	}
};

// simple
typedef policy::WidgetManager< policy::OpNewCreator<Widget> > MyWidgetMgr;


void test_policy(){
	Widget* m_widget = MyWidgetMgr::Create();
	delete m_widget;
}

void test_policy_template(){
	Widget* m_widget = policy::WidgetManager2<policy::OpNewCreator>::Create();
	delete m_widget;
	Widget* m_widget_default = policy::WidgetManager2<>::Create();
	delete m_widget_default;
}

void test_policy_destructor(){
	policy::WidgetManager2<> wtmgr;
	policy::OpNewCreator<Widget> * opCreator = &wtmgr;
	//delete opCreator; // because deconstructor is protected, the compiler will point the error!
	policy::WidgetManager2<policy::PrototypeCreator> wtmgr2;
	policy::PrototypeCreator<Widget> * protyCreator = &wtmgr2;
	//delete protyCreator;
}

void test_optional_funciton_of_incomplete_ins(){
	policy::WidgetManager2<policy::PrototypeCreator> wtmgr2;
	Widget * newWidget = new Widget;
	wtmgr2.SwitchPrototype(newWidget);

	policy::WidgetManager2<policy::OpNewCreator> wtmgr2_2;
	Widget * newWidget_2 = new Widget;
	//wtmgr2_2.SwitchPrototype(newWidget_2);  // compiler point error! 


}


int main()
{
	test_policy();
	test_policy_template();
	test_optional_funciton_of_incomplete_ins();
	return -1;
}
