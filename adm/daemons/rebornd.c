
//ת�����������ļ�
#include <ansi.h>

inherit F_DBASE;

#define JINGYAN  "/d/zhuanshi/jingyan/migong1"
#define QILIN  "/d/zhuanshi/qilindong/dongkou"

void jingyan_close(object n_place);
void qilin_close(object place);

mapping dir_list = ([
"����" : "/d/beijing/",
"����" : "/d/changan/",
"����" : "/d/city/",
"�ɶ�" : "/d/city3/",
"����" : "/d/dali/",
"��ɽ" : "/d/foshan/",
"����" : "/d/fuzhou/",
"����" : "/d/guanwai/",
"����" : "/d/hangzhou/",
"��ɽ" : "/d/hengshan/",
"����" : "/d/jingzhou/",
"����" : "/d/kaifeng/",
"��ɽ" : "/d/huashan/",
"����" : "/d/kunming/",
"����" : "/d/lanzhou/",
"����" : "/d/lingzhou/",
"����" : "/d/luoyang/",
"��ɽ" : "/d/songshan/",
"����" : "/d/suzhou/",
"̩ɽ" : "/d/taishan/",
"�䵱ɽ" : "/d/wudang/",
"����" : "/d/xiangyang/",
"����" : "/d/zhongzhou/",
]);

string *place = values(dir_list);
string *c_place = keys(dir_list);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "ת������");
        CHANNEL_D->do_channel( this_object(), "wiz", "ת������������"); 
        //���㹬���
        remove_call_out("jingyan_open");
        call_out("jingyan_open", 350);
       //��������
        remove_call_out("qilin_open");
        call_out("qilin_open", 550);
}

void jingyan_open()
{       
        object n_place;
        string s_place, dir;
        int i;
        int num = random(sizeof(place));
        string city = place[num];

        string *plist = get_dir(city);

        do {       
                s_place = plist[random(sizeof(plist))];     
                //�ļ����к���bak���ļ���Ҫ����������һ��
                if ( strsrch(s_place,"bak") > -1 ) continue; 
                //����c�ļ���Ҳ�˹�
                i = sizeof(s_place);
                if ( s_place[(i-2)..i] != ".c" ) continue;
                //����÷����Ѿ��������ڴ����ֱ��find
                //find����˵��û�������ڴ���Ǿ�load���� 
                //loadҲload��������ž��������ˣ��Ǿ�����һ����   
                if ( ! objectp(n_place = find_object(city + s_place)))
               
                if ( ! objectp(n_place = load_object(city + s_place)))
                   continue; 
           }       
        while(!n_place || !n_place->query("outdoors"));
                
        n_place->set("exits/jingyangong", JINGYAN);

               
       CHANNEL_D->do_channel(this_object(), 
         "wiz", "���㹬������ӵ���" + c_place[num] + city + s_place + "��ע�⡣");
                
       set("jingyan/out", city + s_place); //���ļ����¼���Թ������Ӵ�
                                          
       message("vision", HIG"��" HIR "��������" HIG"��" HIW 
               "�����صľ��㹬���ֽ����ˣ��ƺ���"
               + c_place[num] + "����\n" + NOR,users());
       //10���Ӻ�رգ�ʱ���������

       remove_call_out("jingyan_close");
       call_out("jingyan_close", 600, n_place);      
}

void jingyan_close(object n_place)
{       
     if (n_place && n_place->query("exits/jingyangong"))
     {       
       n_place->delete("exits/jingyangong");       
       message("vision", HIG"��" HIR"��������" HIG"��" HIW"�����صľ��㹬����ʧ�ˡ�\n" 
                      NOR,users());
     }
     remove_call_out("jingyan_open");
   //  call_out("jingyan_open", 3600 * 3); //����Сʱ��һ�ο�
//     call_out("jingyan_open", 1800); //����ʱ����Сʱ��һ�ο�

}

void qilin_open()
{
     object room = find_object("/d/city3/shudao8");
     if (! room)
       room = load_object("/d/city3/shudao8");

    room->set("exits/qilinku", QILIN);
    
     message("vision", HIG"��" HIR"��������" HIG"��" HIW
                "���ɶ������ˮ���ģ�������������䡣\n"NOR,users());
      
    remove_call_out("qilin_close");
    call_out("qilin_close", 600, room); //ʮ���ֺ�ر�
}

void qilin_close(object room)
{
     if ( room && room->query("exits/qilinku"));
         room->delete("exits/qilinku");

     message("vision", HIG"��" HIR"��������" HIG"��" HIW
                "���ɶ������ˮ��ȥ��������ٴ���ʧ��\n"NOR,users());

    remove_call_out("qilin_open");
  //  call_out("qilin_open", 3600 * 6); //����Сʱ��һ�ο�
//   call_out("qilin_open", 1800); //����ʱ����Сʱ��һ�ο�

}



