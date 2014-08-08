#ifndef pi_h
#define pi_h

#include <kparts/plugin.h>

class Pi : public KParts::Plugin
{
    Q_OBJECT
public:
    Pi( QObject* parent, const QVariantList & );
    ~Pi() {}

public slots:
    void calcPi();
};

#endif
