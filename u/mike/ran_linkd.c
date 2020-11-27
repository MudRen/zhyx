//随机地图守护进程
//一个人的那个，我建议做一个守护NPC在/d/jingyan/migong1里
#include <ansi.h>

inherit F_DBASE;

public void close_door();
int num;
object now_place;
//可以添加其他路径目录，注意格式
mapping dir_list = (["华山" : "/d/huashan/*.c",
                                         "恒山" : "/d/hengshan/*.c"
                                        ]);
string *place = values(dir_list);
string *c_place = keys(dir_list);
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "随机地图连接精灵");
        CHANNEL_D->do_channel( this_object(), "wiz", "随机地图连接精灵启动。\n"); 
        remove_call_out("ran_link");
        call_out("ran_link",10);
}

void ran_link()
{       
        object n_place;
        string s_place,dir;
        int num = random(sizeof(place));
        string city = place[num];
        string *plist = get_dir(city);
// 采用do while句型避免过度占用系统资源
        do      {       
                s_place = plist[random(sizeof(plist))];
                plist -= ({ s_place });
                if (strsrch(s_place,"bak") != -1)       continue;//剔除文件中含有bak的路径文件
                n_place = load_object(city[0..<4] + s_place);
                }       while(!n_place->query("outdoors"));
                
                n_place->set("exits/migong","/u/sanben/workroom");//我换了地方，便于测试
                now_place = n_place;
                CHANNEL_D->do_channel( this_object(), "wiz", "连接到了" + c_place[num] + city[0..<4] + s_place + "请注意。");
                
                //chat显示
                message("channel:chat",HIG"【"+HIR"江湖传言"+HIG"】"+HIW"：神秘的惊雁宫重现江湖了，似乎在" + c_place[num] + "方向。\n" + NOR,users());
                //10分钟后关闭，时间可以设置
                remove_call_out("close_door");
                call_out("close_door", 60);
                return;
}

public void close_door()
{       
        if(now_place->query("exits/migong"))
        {       now_place->delete("exits/migong");
                CHANNEL_D->do_channel( this_object(), "wiz", "关闭了。");
                message("channel:chat",HIG"【"+HIR"江湖传言"+HIG"】"+HIW"：神秘的惊雁宫又消失了。\n" + NOR,users());
         }
}

