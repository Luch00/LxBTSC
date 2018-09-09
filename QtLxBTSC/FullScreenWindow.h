#pragma once

#include <QWidget>

class QWebEngineView;

class FullScreenWindow : public QWidget
{
	Q_OBJECT

public:
	FullScreenWindow(QWebEngineView* oldView, QWidget *parent = nullptr);
	~FullScreenWindow();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QWebEngineView* view;
	QWebEngineView* oldView;
	QRect oldGeometry;
};
