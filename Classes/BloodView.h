#ifndef __BLOODVIEW_H__  
#define __BLOODVIEW_H__  

#include "cocos2d.h"  
using namespace cocos2d;

class BloodView : public CCNode
{
public:
	BloodView();

public:
	//����Ѫ������  
	void setBackgroundTexture(const char *pName);
	//����Ѫ��ǰ��  
	void setForegroundTexture(const char *pName);
	//������Ѫ��  
	void setTotalProgress(float total);
	//���õ�ǰѪ��  
	void setCurrentProgress(float progress);
	//�õ���ǰѪ��  
	float getCurrentProgress() const;
	//�õ���Ѫ��  
	float getTotalProgress() const;

private:
	//����ǰ��Ѫ����ʾ�ĳ���  
	void setForegroundTextureRect(const CCRect &rect);

private:
	CCSprite *m_progressBackground;		//����Ѫ��  
	CCSprite *m_progressForeground;		//ǰ��Ѫ��  
	float m_totalProgress;				//��Ѫ��  
	float m_currentProgress;			//��ǰѪ��  
	float m_scale;						//�Ŵ���  
};

#endif //__BLOODVIEW_H__ 