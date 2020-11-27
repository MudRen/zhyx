// This file for hj_wiztools.c and hj_npc_quest.c(the no.1 , seller)
// ���������ļ��������ļ���hj_wiztools.c �� hj_npc_quest.c ��
// ʵ���ϣ������ļ������ǲ�ͬ�ġ�ͳһ�������Ϊ�˷�����ġ�



// ###########################################################
// ################# ��������ʦ�õĸ����б� ##################
// ###########################################################

string *can_copy=({"
    \n"HIY"������"NOR"\n",
"dx����ˮ��","fx����֮ʯ","tl����ˮ��","hg�ع�֮��",
"qd��֮ʯ","zh�ٻ�֮��","fd����֮��","qz����֮��",
"xrѰ��ˮ��","kt��̽ˮ��","dw��λ֮��",

    "\n"HIY"������"NOR"\n",
"wmg������","xrg���˹�","tqg������","dlg������","ysgҰ����ʵ",
"hbs��ɫ��ʯ","lvbs��ɫ��ʯ","lbs��ɫ��ʯ","slg����֮��",


    "\n"HIY"������"NOR"\n",
"qtj��֮ͭ��","lqj����֮��","byj����֮��","ydjӯ��֮��",
"hjj�ƽ�֮��","nlj����֮��","xyjѸ��֮��","dhj���֮��","bsj��ʤ֮��",
"kfsj���ˮ��","bysj����ˮ��","llsj����ˮ��","ydsj����ˮ��","gssj��ʯˮ��",
"fhsj�ɻ�ˮ��","dhsj���ˮ��",

    "\n"HIY"������Ʒ��"NOR"\n",
"hfzs����֮ʯ","hyzs����֮ʯ","llzs����֮ʯ","ydzs����֮ʯ",
"gszs��ʯ֮ʯ","fhs�ɻ�֮ʯ","dhzs���֮ʯ","fhzs����֮ʯ",

    "\n"HIY"������Ʒ��(���ɹ���)"NOR"\n",
"srl�����5����Ч�ܣ�", "box����",
});


mapping all=([

"dx":"����ˮ��","fx":"����֮ʯ","tl":"����ˮ��","hg":"�ع�֮��","qd":"��֮ʯ",
"zh":"�ٻ�֮��","fd":"����֮��","qz":"����֮��","xr":"Ѱ��ˮ��","kt":"��̽ˮ��",
"dw":"��λ֮��",

"wmg":"������","xrg":"���˹�","tqg":"������","dlg":"������","ysg":"Ұ����ʵ",
"hbs":"��ɫ��ʯ","lvbs":"��ɫ��ʯ","lbs":"��ɫ��ʯ","slg":"����֮��",


"qtj":"��֮ͭ��","lqj":"����֮��","byj":"����֮��","ydj":"ӯ��֮��",
"hjj":"�ƽ�֮��","nlj":"����֮��","xyj":"Ѹ��֮��","dhj":"���֮��","bsj":"��ʤ֮��",


"kfsj":"���ˮ��","bysj":"����ˮ��","llsj":"����ˮ��","ydsj":"����ˮ��",
"gssj":"��ʯˮ��","fhsj":"�ɻ�ˮ��","dhsj":"���ˮ��",

"hfzs":"����֮ʯ","hyzs":"����֮ʯ","llzs":"����֮ʯ","ydzs":"����֮ʯ",
"gszs":"��ʯ֮ʯ","fhs":"�ɻ�֮ʯ","dhzs":"���֮ʯ","fhzs":"����֮ʯ",

"srl":"������(5���ӵ�)", "box":"����",

    ]);



mapping all_dir=([

"dx":"hj_obj_tools","fx":"hj_obj_tools","tl":"hj_obj_tools","hg":"hj_obj_tools",
"qd":"hj_obj_tools","zh":"hj_obj_tools","fd":"hj_obj_tools","qz":"hj_obj_tools",
"xr":"hj_obj_tools","kt":"hj_obj_tools","dw":"hj_obj_tools",

"wmg":"hj_obj_other","xrg":"hj_obj_other","tqg":"hj_obj_other",
"dlg":"hj_obj_other","ysg":"hj_obj_other","hbs":"hj_obj_other",
"lvbs":"hj_obj_other","lbs":"hj_obj_other","slg":"hj_obj_other",

"qtj":"hj_obj_weapon","lqj":"hj_obj_weapon","byj":"hj_obj_weapon","ydj":"hj_obj_weapon",
"hjj":"hj_obj_weapon","nlj":"hj_obj_weapon","xyj":"hj_obj_weapon","dhj":"hj_obj_weapon",
"bsj":"hj_obj_weapon","kfsj":"hj_obj_weapon","bysj":"hj_obj_weapon",
"llsj":"hj_obj_weapon","ydsj":"hj_obj_weapon","gssj":"hj_obj_weapon",
"fhsj":"hj_obj_weapon","dhsj":"hj_obj_weapon",

"hfzs":"hj_obj_quest","hyzs":"hj_obj_quest","llzs":"hj_obj_quest","ydzs":"hj_obj_quest",
"gszs":"hj_obj_quest","fhs":"hj_obj_quest","dhzs":"hj_obj_quest","fhzs":"hj_obj_quest",
"srl":"shenren_ling","box":"hj_box",
    ]);

mapping all_set=([

"dx":111,"fx":1,"tl":2,"hg":3,"qd":4,"zh":5,"fd":6,"qz":7,"xr":8,"kt":9, "dw":10,

"wmg":111,"xrg":1,"tqg":2,"dlg":3,"ysg":4,
"hbs":5,"lvbs":6,"lbs":7,"slg":8,

"qtj":111,"lqj":1,"byj":2,"ydj":3,
"hjj":4,"nlj":5,"xyj":6,"dhj":7,"bsj":8,

"kfsj":9,"bysj":10,"llsj":11,"ydsj":12,
"gssj":13,"fhsj":14,"dhsj":15,

"hfzs":111,"hyzs":1,"llzs":2,"ydzs":3,"gszs":4,"fhs":5,"dhzs":6,"fhzs":7,
"srl":1024, "box":1024,
// ��� srl(������) �� set �ķ����Ѹ��ģ��������ֵ���������ˡ�
    ]);

// ������ʱ��ѧ���� mapping ���÷������� hj_wiz_tools.c ���
// list����д���й��ޱ��İ�����


// ###########################################################
// ################# ����������õ������б� ##################
// ###########################################################

mapping can_sell_tools=([   // ����

"dx":"����ˮ��","fx":"����֮ʯ","tl":"����ˮ��","hg":"�ع�֮��","test":"������",
"qd":"��֮ʯ","zh":"�ٻ�֮��","fd":"����֮��","qz":"����֮��","xr":"Ѱ��ˮ��",
"kt":"��̽ˮ��","dw":"��λ֮��",
    ]);

mapping can_sell_other=([   // ��Ʒ��

"wmg":"������","xrg":"���˹�","tqg":"������","dlg":"������",
"ysg":"Ұ����ʵ","slg":"����֮��"
    ]);

mapping can_sell_weapon=([   // ������

"qtj":"��֮ͭ��","lqj":"����֮��","byj":"����֮��","ydj":"ӯ��֮��",
"hjj":"�ƽ�֮��","nlj":"����֮��","xyj":"Ѹ��֮��","dhj":"���֮��","bsj":"��ʤ֮��",
"kfsj":"���ˮ��","bysj":"����ˮ��","llsj":"����ˮ��","ydsj":"����ˮ��","gssj":"��ʯˮ��",
"fhsj":"�ɻ�ˮ��","dhsj":"���ˮ��"
    ]);

mapping can_sell_quest=([    // ����

"hfzs":"����֮ʯ","hyzs":"����֮ʯ","llzs":"����֮ʯ","ydzs":"����֮ʯ",
"gszs":"��ʯ֮ʯ","fhs":"�ɻ�֮ʯ","dhzs":"���֮ʯ","fhzs":"����֮ʯ"
    ]);


// ���ļ��ڼ�¼�����ߵļ۸�
#include "obj_values.h"
