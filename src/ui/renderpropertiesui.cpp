#include "renderpropertiesui.h"
#include "ui_renderpropertiesui.h"

#include <QFileDialog>

RenderPropertiesUI::RenderPropertiesUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderPropertiesUI)
{
    ui->setupUi(this);
    ui->constantFrame->setEnabled(ui->backgroundConstant->isChecked());
    ui->gradientFrame->setEnabled(ui->backgroundGradient->isChecked());
    ui->imageFrame->setEnabled(ui->backgroundImage->isChecked());

	connect(ui->backgroundConstantButton, SIGNAL(beginUserInteraction(void)), 
			this, SLOT(onBeginUserInteraction(void)));
	connect(ui->backgroundGradientFromButton, SIGNAL(beginUserInteraction(void)), 
			this, SLOT(onBeginUserInteraction(void)));
	connect(ui->backgroundGradientToButton, SIGNAL(beginUserInteraction(void)), 
			this, SLOT(onBeginUserInteraction(void)));
	connect(ui->backgroundConstantButton, SIGNAL(endUserInteraction(void)), 
			this, SLOT(onEndUserInteraction(void)));
	connect(ui->backgroundGradientFromButton, SIGNAL(endUserInteraction(void)), 
			this, SLOT(onEndUserInteraction(void)));
	connect(ui->backgroundGradientToButton, SIGNAL(endUserInteraction(void)), 
			this, SLOT(onEndUserInteraction(void)));
}

RenderPropertiesUI::~RenderPropertiesUI()
{
    delete ui;
}

void RenderPropertiesUI::onPathtracerMaxSamplesChanged(int value)
{
    emit pathtracerMaxSamplesChanged(value);
}

void RenderPropertiesUI::onPathtracerMaxPathBouncesChanged(int value)
{
    emit pathtracerMaxPathBouncesChanged(value);
}

void RenderPropertiesUI::onResolutionSettingsChanged()
{
    emit resolutionSettingsChanged();
}
void RenderPropertiesUI::onWireframeOpacityChanged(int value)
{
	emit wireframeOpacityChanged(value);
}

void RenderPropertiesUI::onWireframeThicknessChanged(int value)
{
	emit wireframeThicknessChanged(value);
}

void RenderPropertiesUI::getResolutionSettings(ResolutionMode &mode, int &axis1, int &axis2)
{
    if (!ui) return;
    axis1 = 0;
    axis2 = 0;

    if (ui->resolutionFixedRadioButton->isChecked())
    {
        mode = RM_FIXED;
        axis1 = ui->resolutionFixedWidthSpinBox->value();
        axis2 = ui->resolutionFixedHeightSpinBox->value();
    }
    else if(ui->resolutionLongestAxisRadioButton->isChecked())
    {
        mode = RM_LONGEST_AXIS;
        axis1 = ui->resolutionLongestAxisSpinBox->value();
    }
    else
    {
        mode = RM_MATCH_WINDOW;
    }
}

void RenderPropertiesUI::onBackgroundColorChangedConstant(QColor color)
{
	emit backgroundColorChangedConstant(color);
}
void RenderPropertiesUI::onBackgroundColorChangedGradientFrom(QColor color)
{
	emit backgroundColorChangedGradientFrom(color);
}
void RenderPropertiesUI::onBackgroundColorChangedGradientTo(QColor color)
{
	emit backgroundColorChangedGradientTo(color);
}
void RenderPropertiesUI::onBackgroundColorChangedImage(QString path)
{
	emit backgroundColorChangedImage(path);
}

void RenderPropertiesUI::onBackgroundImageRotationChanged(int rotation)
{
	emit backgroundImageRotationChanged(rotation);
}

void RenderPropertiesUI::setBackground(QColor constantColor)
{
	ui->backgroundConstantButton->setColor(constantColor);
	ui->backgroundConstant->setChecked(true);
}
void RenderPropertiesUI::setBackground(QColor gradientFrom, QColor gradientTo)
{
	ui->backgroundGradientFromButton->setColor(gradientFrom);
	ui->backgroundGradientToButton->setColor(gradientTo);
	ui->backgroundGradient->setChecked(true);
}
void RenderPropertiesUI::setBackground(QString image)
{
	ui->backgroundImage->setChecked(true);
}

void RenderPropertiesUI::onBackgroundColorConstant()
{
	onBackgroundColorChangedConstant(ui->backgroundConstantButton->getColor());
}
void RenderPropertiesUI::onBackgroundColorGradient()
{
	onBackgroundColorChangedGradientFrom(ui->backgroundGradientFromButton->getColor());
	onBackgroundColorChangedGradientTo(ui->backgroundGradientToButton->getColor());
}
void RenderPropertiesUI::onBackgroundColorImage()
{
	onBackgroundColorChangedImage(ui->backgroundImagePath->text());
}

void RenderPropertiesUI::onBackgroundImageBrowseClicked()
{
	emit beginUserInteraction();

    QFileDialog dialog(QApplication::activeWindow());

    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Image files (*.jpg *.png *.exr *.hdr *.tiff)"));
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        QString file = dialog.selectedFiles()[0];
        ui->backgroundImagePath->setText(file);
		emit backgroundColorChangedImage(file);
    }

	emit endUserInteraction();
}
#include <iostream>
void RenderPropertiesUI::onBeginUserInteraction()
{
	// propagate signal to parent widget
	emit beginUserInteraction();
}

void RenderPropertiesUI::onEndUserInteraction()
{
	// propagate signal to parent widget
	emit endUserInteraction();
}


