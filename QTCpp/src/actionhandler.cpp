
#include "actionhandler.h"
#include "Tools/chartmarker.h"
#include <Tools/chartpointer.h>

CActionHandler::CActionHandler(QCustomPlot *plot)
    : QObject{plot}
{
    plot->addLayer(PLOT_TOOL_LAYER_NAME);

    PlotTools.insert_or_assign(EToolType::Marker,new CChartMarkerBuilder(plot));
    PlotTools.insert_or_assign(EToolType::Pointer,new CChartPointerBuilder(plot));

    // TO DO : insert other tools one by one after implementation
}

void CActionHandler::SetPlotEvent(QMouseEvent *e)
{
    auto tool = PlotTools.find(ActiveToolType);
    if(tool != PlotTools.end())
        tool->second->UpdateWithMouseEvent(e);
}

void CActionHandler::UpdateView()
{
    auto tool = PlotTools.find(ActiveToolType);
    if(tool != PlotTools.end())
        tool->second->UpdateView();
}

void CActionHandler::SetActiveTool(EToolType mode)
{
    ActiveToolType = mode;
}


