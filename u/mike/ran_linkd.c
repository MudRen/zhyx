//�����ͼ�ػ�����
//һ���˵��Ǹ����ҽ�����һ���ػ�NPC��/d/jingyan/migong1��
#include <ansi.h>

inherit F_DBASE;

public void close_door();
int num;
object now_place;
//�����������·��Ŀ¼��ע���ʽ
mapping dir_list = (["��ɽ" : "/d/huashan/*.c",
                                         "��ɽ" : "/d/hengshan/*.c"
                                        ]);
string *place = values(dir_list);
string *c_place = keys(dir_list);
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "�����ͼ���Ӿ���");
        CHANNEL_D->do_channel( this_object(), "wiz", "�����ͼ���Ӿ���������\n"); 
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
// ����do while���ͱ������ռ��ϵͳ��Դ
        do      {       
                s_place = plist[random(sizeof(plist))];
                plist -= ({ s_place });
                if (strsrch(s_place,"bak") != -1)       continue;//�޳��ļ��к���bak��·���ļ�
                n_place = load_object(city[0..<4] + s_place);
                }       while(!n_place->query("outdoors"));
                
                n_place->set("exits/migong","/u/sanben/workroom");//�һ��˵ط������ڲ���
                now_place = n_place;
                CHANNEL_D->do_channel( this_object(), "wiz", "���ӵ���" + c_place[num] + city[0..<4] + s_place + "��ע�⡣");
                
                //chat��ʾ
                message("channel:chat",HIG"��"+HIR"��������"+HIG"��"+HIW"�����صľ��㹬���ֽ����ˣ��ƺ���" + c_place[num] + "����\n" + NOR,users());
                //10���Ӻ�رգ�ʱ���������
                remove_call_out("close_door");
                call_out("close_door", 60);
                return;
}

public void close_door()
{       
        if(now_place->query("exits/migong"))
        {       now_place->delete("exits/migong");
                CHANNEL_D->do_channel( this_object(), "wiz", "�ر��ˡ�");
                message("channel:chat",HIG"��"+HIR"��������"+HIG"��"+HIW"�����صľ��㹬����ʧ�ˡ�\n" + NOR,users());
         }
}

