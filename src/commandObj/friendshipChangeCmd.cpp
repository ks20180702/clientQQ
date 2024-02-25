#include "./include/friendshipChangeCmd.h"

CFriendshipChangeCmd::CFriendshipChangeCmd()
    :_myUser(),_friendUser(){ _childCmdType=FRIEND_SHIP_CHANGE_CMD;}

CFriendshipChangeCmd::CFriendshipChangeCmd(CUser &myUser,CUser &friendUser,OperatorFriendShipType friendType)
{
    _myUser=myUser;
    _friendUser = friendUser;
    _friendType=friendType;
    _childCmdType=FRIEND_SHIP_CHANGE_CMD;
}
int CFriendshipChangeCmd::do_command()
{
    // _childDoCommandReturn=false;

    // int dealOperRe=0;
    // if(_friendType==DELETT_FRIEND)
    // {
    //     cmdOtlUse.set_user_id_by_account(_myUser);
    //     cmdOtlUse.set_user_id_by_account(_friendUser);
    //     dealOperRe=cmdOtlUse.del_friendship(_myUser.get_id(),_friendUser.get_id());
    // }
    // else if(_friendType==ADD_FRIEND)
    // {
    //     // dealOperRe=cmdOtlUse
    // }

    // if(dealOperRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return -1;}

    // _childDoCommandReturn=true; //执行结束

    // std::cout<<"do command is succeed"<<std::endl;
    return 0;
}

std::string CFriendshipChangeCmd::get_command_obj_json()
{
    std::ostringstream ostrStream;
    cereal::JSONOutputArchive jsonOA(ostrStream);
    super_json_add_make_nvp(jsonOA,this->_childCmdType);
    
    jsonOA(cereal::make_nvp("friendShipInfo", *this));
    return ostrStream.str();
}

void CFriendshipChangeCmd::set_user(CUser &myUser)
{
    _myUser=myUser;
}
void CFriendshipChangeCmd::set_friend_user(CUser &friendUser)
{
    _friendUser = friendUser;
}
void CFriendshipChangeCmd::set_operator_type(OperatorFriendShipType friendType)
{
    _friendType=friendType;
}
CFriendshipChangeCmd::~CFriendshipChangeCmd()
{

}
