// std::vector<CDataBase*> test2(CDataCmd *dataInfo)
// {
// 	return dataInfo->get_data_vector_value();

int main()
{
	std::cout<<"main +++"<<std::endl;

	CDataCmd dataInfo;
	std::vector<CDataBase*> dataVec2;
	CUserNotRecvMsg userMsg1(10,"1号",2);
	CUserNotRecvMsg userMsg2(11,"2号",3);
	CUserNotRecvMsg userMsg3(12,"3号",1);
	dataInfo.add_data_info(&userMsg1);
	dataInfo.add_data_info(&userMsg2);
	dataInfo.add_data_info(&userMsg3);

	dataVec2=test2(&dataInfo);
	for(vector<CDataBase*>::iterator it=dataVec2.begin();it!=dataVec2.end();it++)
	{
		((CUserNotRecvMsg*)*it)->print();
	}
}

